#include <pybind11/embed.h>
#include <Python.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include "binding.h"
#include <bundle/bb_text_extractor.h>
#include <bundle/base_library.h>
#include <bundle/purepython.h>

using namespace std::chrono_literals;
namespace py = pybind11;
void register_memory_importer(py::module_ &m);
void register_physfs(py::module_ &m);
void register_nutcracker(py::module_ &m);


PYBIND11_EMBEDDED_MODULE(memory_importer, m) {
    register_memory_importer(m);
    py::module mPhysfs = m.def_submodule("physfs", "physfs lib");
    register_physfs(mPhysfs);
}

PYBIND11_EMBEDDED_MODULE(_nutcracker, m) {
    register_nutcracker(m);
    m.attr("__version__") = "embed";
    m.attr("__author__") = "shabbywu<shabbywu@qq.com>";
}


std::thread daemon_thread;
std::unique_ptr<py::scoped_interpreter> guard;
std::unique_ptr<py::gil_scoped_release> release;
std::mutex mtx;


void daemon_worker_thread(AppState *state) {
    state->addLog("[*] worker daemon started");
    while (!state->appShallExit)
    {
        mtx.lock();
        {
            py::gil_scoped_acquire acquire;
            auto sys = py::module_::import("sys");
            py::exec(R"(
                from pathlib import Path
                from bb_text_extractor import extractor
                if queues:
                    data_path, dest_path  = queues.pop(0)
                    extractor.set_log(addLog)
                    extractor.core(Path(data_path), Path(dest_path))
            )", py::globals());
        }
        mtx.unlock();
        std::this_thread::sleep_for(100ms);
    }
    state->addLog("[*] worker daemon exited");
    state->gracefulExit = true;
}

// start python interpreter and daemon worker
void start_python_daemon(AppState *state) {
    {
        putenv("PYTHONIOENCODING=utf-8");
        // 设置目录
        const auto pythonRootDir = (state->pythonRootDir).wstring();

        auto & pybaseLibrary = bin2cpp::getBase_libraryZipFile();
        if (!pybaseLibrary.save((state->pythonRootDir / pybaseLibrary.getFileName()).c_str())) {
            state->addLog("Failed to start daemon worker");
            return;
        }

        #ifdef _WIN32
            auto pythonHome = pythonRootDir + L"\\";
            auto pythonPath = pythonRootDir + L"\\base_library.zip;";
        #else
            auto pythonHome = pythonRootDir + L"/";
            auto pythonPath = pythonRootDir + L"/base_library.zip:" + pythonRootDir + L":"+ pythonRootDir + L"/lib-dynload:";
        #endif

        Py_SetProgramName(L"bb-text-extractor");
        Py_SetPath(pythonPath.c_str());

        guard = std::make_unique<py::scoped_interpreter>();
        // ensure python object will release before gil_scoped_release
        {
            auto physfs = py::module_::import("memory_importer.physfs");
            physfs.attr("init")();

            auto & purePython = bin2cpp::getPurepythonZipFile();
            auto purePython_buffer = py::memoryview::from_memory(purePython.getBuffer(), purePython.getSize());
            physfs.attr("mount_memory")(purePython_buffer, purePython.getFileName(), "/");

            auto & core = bin2cpp::getBb_text_extractorZipFile();
            auto core_buffer = py::memoryview::from_memory(core.getBuffer(), core.getSize());
            physfs.attr("mount_memory")(core_buffer, core.getFileName(), "/");

            // install memory importer as package finder
            auto sys = py::module_::import("sys");
            auto obj = py::module_::import("memory_importer").attr("PhysfsImporter")();
            // obj.attr("__setattr__")("debug", true);
            sys.attr("meta_path").attr("append")(obj);

            // register method
            auto globals = py::globals();
            globals["addLog"] = py::cpp_function([state](py::object message) {
                state->addLog(std::string(py::str(message)));
            });
            globals["queues"] = py::list();
        }
        // release gil for multi-threading
        release = std::make_unique<py::gil_scoped_release>();
    }

    daemon_thread = std::thread(daemon_worker_thread, state);
}

void shutdown_python_daemon(AppState *state) {
    daemon_thread.detach();
    while (!state->gracefulExit)
    {
        std::this_thread::sleep_for(100ms);
    }
    release = nullptr;
    guard = nullptr;
}


void dispatch_extractor(AppState *state) {
    if (state->appShallExit) return;
    try
    {
        mtx.try_lock();
        {
            py::gil_scoped_acquire acquire;
            py::dict locals;
            locals["task"] = py::make_tuple(state->dataDir.string(), state->destDir.string());
            py::exec(R"(
                if queues:
                    addLog("上一个任务尚未完成...")
                else:
                    queues.append(task)
            )", py::globals(), locals);
        }
        mtx.unlock();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

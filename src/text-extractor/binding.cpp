#include <pybind11/embed.h>
#include <Python.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include "binding.h"

using namespace std::chrono_literals;
namespace py = pybind11;
void register_memory_importer(py::module_ &m);
void register_physfs(py::module_ &m);


PYBIND11_EMBEDDED_MODULE(memory_importer, m) {
    register_memory_importer(m);
    py::module mPhysfs = m.def_submodule("physfs", "physfs lib");
    register_physfs(mPhysfs);
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
            py::exec(R"(
                if queues:
                    task = queues.pop(0)
            )");
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
        guard = std::make_unique<py::scoped_interpreter>();
        // TODO: add meta_path
        // py::module_::import("sys").attr("meta_path").attr("append")();
        // ensure python object will release before gil_scoped_release
        {
            auto globals = py::globals();
            globals["addLog"] = py::cpp_function([state](py::object message) {
                state->addLog(std::string(py::str(message)));
            });
            globals["queues"] = py::list();
            py::exec(R"(
                import sys
                from memory_importer import physfs, PhysfsImporter

                physfs.init()
                # TODO: mount libraries to physfs
                sys.meta_path.append(PhysfsImporter())
            )");
        }
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
            py::exec("a = 1");
        }
        mtx.unlock();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

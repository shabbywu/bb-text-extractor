#include <pybind11/embed.h>
#include <Python.h>
#include "iostream"



namespace py = pybind11;
void register_physfs(py::module_ &m);


PYBIND11_EMBEDDED_MODULE(physfs, m) {
    // `m` is a `py::module_` which is used to bind functions and classes
    register_physfs(m);
}



void run_python() {
    try {
        py::scoped_interpreter guard{};
        py::dict locals;
        py::exec(R"(
            import sys
            print(sys.version_info)
        )");
    } catch(const std::exception& e) {
        std::cerr << "unknown error occurred: " << e.what() << '\n';
    }
}
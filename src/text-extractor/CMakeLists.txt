find_package(Python3 COMPONENTS Development REQUIRED)
find_package(pybind11 CONFIG)
add_subdirectory(${physfs_py_dir} build)


file(GLOB source_text_extractor
    *.cpp
    *.h
    physfs_shim/*.cpp
    physfs_shim/*.h
)


add_library(text_extractor_core STATIC ${source_text_extractor})
target_include_directories(text_extractor_core PRIVATE ${PHYSFS_INCLUDE_DIR})
target_link_libraries(text_extractor_core PRIVATE ${PHYSFS_LIBRARY} pybind11::embed physfs_py_static)

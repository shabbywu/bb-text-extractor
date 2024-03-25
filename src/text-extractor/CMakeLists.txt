if(NOT DEFINED Python_EXECUTABLE)
  find_package(
    Python3
    COMPONENTS Development
    REQUIRED)
endif()
find_package(pybind11 CONFIG)
# build memory-importer
add_subdirectory(${memory_importer_dir} memory-importer)

# pack scripts bundle and move to assets
set(PACK_BB_TEXT_EXTRACTOR TRUE)
add_subdirectory(${py_scripts_dir}/cmake/pack scripts-bundle)

set(python-bundle-dir
    ${CMAKE_CURRENT_BINARY_DIR}/scripts-bundle/bb-text-extractor/bundle)

file(GLOB source_text_extractor binding.cpp binding.h
     ${python-bundle-dir}/*.cpp ${python-bundle-dir}/embedfiles/*.h)

add_library(text_extractor_core STATIC ${source_text_extractor})
target_include_directories(text_extractor_core PRIVATE ${PHYSFS_INCLUDE_DIR}
                                                       ${python-bundle-dir}/..)
target_link_libraries(
  text_extractor_core PRIVATE pybind11::embed Python3::Python
                              memory-importer-static)

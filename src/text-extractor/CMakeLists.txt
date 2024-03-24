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
set(PACK_BB_TEXT_EXTRACTOR TRUE )
add_subdirectory(${py_scripts_dir}/cmake/pack scripts-bundle)
set(python-bundle-dir ${CMAKE_CURRENT_BINARY_DIR}/scripts-bundle/bb-text-extractor/build/dist/bb_text_extractor)
file(COPY 
  ${python-bundle-dir}/python.zip ${python-bundle-dir}/purepython.zip ${python-bundle-dir}/base_library.zip ${python-bundle-dir}/bb_text_extractor.zip 
  DESTINATION ${assets_dir}/python
)


file(GLOB source_text_extractor binding.cpp binding.h)

add_library(text_extractor_core STATIC ${source_text_extractor})
target_include_directories(text_extractor_core PRIVATE ${PHYSFS_INCLUDE_DIR})
target_link_libraries(text_extractor_core PRIVATE pybind11::embed Python3::Python
                                                  memory-importer-static)

set(CMAKE_CXX_STANDARD 17)
find_package(
  Python3
  COMPONENTS Development
  REQUIRED)
find_package(pybind11 CONFIG)
# build memory-importer
add_subdirectory(${memory_importer_dir} memory-importer)
# build nutcracker
set(SQUIRREL305 TRUE)
add_subdirectory(${nutcracker_dir} nutcracker)
# build zip
add_subdirectory(${zip_dir} zip)

# pack scripts bundle and move to assets
set(PACK_BB_TEXT_EXTRACTOR TRUE)
add_subdirectory(${py_scripts_dir}/cmake/pack scripts-bundle)

set(python-cppbundle-dir
    ${CMAKE_CURRENT_BINARY_DIR}/scripts-bundle/bb-text-extractor/bundle)
set(python-zipbundle-dir
    ${CMAKE_CURRENT_BINARY_DIR}/scripts-bundle/bb-text-extractor/build/bundle)

# 嵌入压缩包
file(GLOB source_text_extractor binding.cpp binding.h
     ${python-cppbundle-dir}/*.cpp ${python-cppbundle-dir}/*.h)

add_library(text_extractor_core STATIC ${source_text_extractor})
target_include_directories(
  text_extractor_core PRIVATE ${PHYSFS_INCLUDE_DIR} ${python-cppbundle-dir}/..
                              ${zip_dir}/src/)
target_link_libraries(
  text_extractor_core PRIVATE pybind11::embed Python3::Python zip
                              memory-importer-static nutcrackercpp)

if(MSVC)
  target_compile_options(text_extractor_core PRIVATE /bigobj)
endif(MSVC)

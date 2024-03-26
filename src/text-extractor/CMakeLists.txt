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

# pack scripts bundle and move to assets
set(PACK_BB_TEXT_EXTRACTOR TRUE)
add_subdirectory(${py_scripts_dir}/cmake/pack scripts-bundle)

set(python-cppbundle-dir
    ${CMAKE_CURRENT_BINARY_DIR}/scripts-bundle/bb-text-extractor/bundle)
set(python-zipbundle-dir
    ${CMAKE_CURRENT_BINARY_DIR}/scripts-bundle/bb-text-extractor/build/bundle)

# 嵌入压缩包
file(
  GLOB
  source_text_extractor
  binding.cpp
  binding.h
  ${python-cppbundle-dir}/bb_text_extractor.cpp
  ${python-cppbundle-dir}/embedfiles/bb_text_extractor.h
  ${python-cppbundle-dir}/base_library.cpp
  ${python-cppbundle-dir}/embedfiles/base_library.h
  ${python-cppbundle-dir}/purepython.cpp
  ${python-cppbundle-dir}/embedfiles/purepython.h)
# 解压二进制依赖
execute_process(
  COMMAND
    ${Python3_EXECUTABLE} -m zipfile -e ${python-zipbundle-dir}/python.zip
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/python)

add_library(text_extractor_core STATIC ${source_text_extractor})
target_include_directories(
  text_extractor_core PRIVATE ${PHYSFS_INCLUDE_DIR} ${python-cppbundle-dir}/..)
target_link_libraries(
  text_extractor_core PRIVATE pybind11::embed Python3::Python
                              memory-importer-static nutcrackercpp)

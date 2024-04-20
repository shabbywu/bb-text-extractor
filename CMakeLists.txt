cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

set(GLFW_LIBRARY_TYPE "STATIC")
set(VCPKG_OVERLAY_PORTS "${CMAKE_CURRENT_LIST_DIR}/.vcpkg/ports/physfs"
                        "${CMAKE_CURRENT_LIST_DIR}/.vcpkg/ports/glfw3")
set(VCPKG_OVERLAY_TRIPLETS "${CMAKE_CURRENT_LIST_DIR}/.vcpkg/triplets")
# Enable VCPKG if VCPKG_ROOT defined.
set(vcpkg "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
if(NOT CMAKE_TOOLCHAIN_FILE AND EXISTS "${vcpkg}")
  set(CMAKE_TOOLCHAIN_FILE
      "${vcpkg}"
      CACHE FILEPATH "CMake toolchain file")
  message(STATUS "vcpkg toolchain found: ${CMAKE_TOOLCHAIN_FILE}")
endif()

# Build your app
# ==============
project(bb-text-extractor)

set(CMAKE_BUILD_TYPE "Release")
set(textedit_dir ${CMAKE_CURRENT_LIST_DIR}/external/ImGuiColorTextEdit)
set(fplus_dir ${CMAKE_CURRENT_LIST_DIR}/external/FunctionalPlus/include)
set(imgui_markdown_dir ${CMAKE_CURRENT_LIST_DIR}/external/imgui_markdown)
set(memory_importer_dir
    ${CMAKE_CURRENT_LIST_DIR}/external/python-memory-importer)
set(py_scripts_dir ${CMAKE_CURRENT_LIST_DIR}/external/py-scripts)
set(nutcracker_dir ${CMAKE_CURRENT_LIST_DIR}/external/NutCracker)
set(zip_dir ${CMAKE_CURRENT_LIST_DIR}/external/zip)

set(assets_dir ${CMAKE_CURRENT_LIST_DIR}/assets)
set(temp_assets_dir ${CMAKE_CURRENT_BINARY_DIR}/temp_assets)

# rename all .bin2app to .cpp
file(GLOB_RECURSE EMBED_CPP "**/*.bin2cpp")
foreach(filename ${EMBED_CPP})
  string(REPLACE ".bin2cpp" ".cpp" filename_cpp ${filename})
  file(COPY_FILE ${filename} ${filename_cpp})
endforeach()
add_subdirectory(src)

# hello_imgui_add_app is a helper function, similar to cmake's "add_executable"
# Usage: hello_imgui_add_app(app_name file1.cpp file2.cpp ...)
#
# Features: * It will automatically link the target to the required libraries
# (hello_imgui, OpenGl, glad, etc) * It will embed the assets (for desktop,
# mobile, and emscripten apps) * It will perform additional customization (app
# icon and name on mobile platforms, etc)

# Now you can build your app with mkdir build && cd build && cmake .. && cmake
# --build .

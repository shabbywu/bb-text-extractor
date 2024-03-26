cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

set(VCPKG_OVERLAY_PORTS "${CMAKE_CURRENT_LIST_DIR}/.vcpkg/ports/physfs")
set(VCPKG_OVERLAY_TRIPLETS "${CMAKE_CURRENT_LIST_DIR}/.vcpkg/triplets")
# Enable VCPKG if VCPKG_ROOT defined.
if(DEFINED ENV{VCPKG_ROOT})
  set(CMAKE_TOOLCHAIN_FILE
      "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE FILEPATH "")
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
set(assets_dir ${CMAKE_CURRENT_LIST_DIR}/assets)
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

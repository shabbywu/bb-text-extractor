cmake_minimum_required(VERSION 3.12)
project(helloworld_with_helloimgui)
set(CMAKE_CXX_STANDARD 17)

# Build hello_imgui
# =================
# via vcpkg i/ You can install hello_imgui via vcpkg with: vcpkg install
# "hello-imgui[opengl3-binding,glfw-binding]" ii/ Then you can use it inside
# CMake with:
find_package(hello-imgui CONFIG REQUIRED)

# Build your app
# ==============
set(textedit_dir ${CMAKE_CURRENT_LIST_DIR}/external/ImGuiColorTextEdit)
set(fplus_dir ${CMAKE_CURRENT_LIST_DIR}/external/FunctionalPlus/include)
set(imgui_markdown_dir ${CMAKE_CURRENT_LIST_DIR}/external/imgui_markdown)
set(memory_importer_dir
    ${CMAKE_CURRENT_LIST_DIR}/external/python-memory-importer)
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

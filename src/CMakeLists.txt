set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Freetype REQUIRED)
find_package(hello-imgui CONFIG REQUIRED)
include(FindPkgConfig)
pkg_check_modules(GLFW3 REQUIRED glfw3)
find_package(OpenGL REQUIRED)

add_subdirectory(ui/imgui_utilities)
add_subdirectory(ui/source_parse)
add_subdirectory(text-extractor)

file(GLOB sources_bb_text_extractor ${CMAKE_CURRENT_LIST_DIR}/*.h
     ${CMAKE_CURRENT_LIST_DIR}/*.cpp ${CMAKE_CURRENT_LIST_DIR}/ui/*.h
     ${CMAKE_CURRENT_LIST_DIR}/ui/*.cpp)

hello_imgui_add_app(bb_text_extractor ${sources_bb_text_extractor}
                    ASSETS_LOCATION ${assets_dir})
target_link_libraries(bb_text_extractor PUBLIC imgui_utilities source_parse
                                               text_extractor_core)
target_include_directories(
  bb_text_extractor
  PUBLIC ${GLFW3_INCLUDE_DIRS} ${textedit_dir} ${fplus_dir}
         ${imgui_markdown_dir} ${GLFW3_LIBRARIES} ${OPENGL_LIBRARIES})
target_link_directories(bb_text_extractor PUBLIC ${GLFW3_LIBRARY_DIRS})
target_compile_options(bb_text_extractor PUBLIC ${GLFW3_CFLAGS_OTHER})

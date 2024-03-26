set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Freetype REQUIRED)
find_package(hello-imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
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
                                               text_extractor_core glfw)
target_include_directories(
  bb_text_extractor
  PUBLIC ${GLFW3_INCLUDE_DIRS} ${textedit_dir} ${fplus_dir}
         ${imgui_markdown_dir} ${GLFW3_LIBRARIES} ${OPENGL_LIBRARIES})

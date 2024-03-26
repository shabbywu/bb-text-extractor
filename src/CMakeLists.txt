set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Freetype REQUIRED)
find_package(hello-imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(ui/imgui_utilities)
add_subdirectory(ui/source_parse)
add_subdirectory(text-extractor)

file(
  GLOB
  sources_bb_text_extractor
  ${CMAKE_CURRENT_LIST_DIR}/*.h
  ${CMAKE_CURRENT_LIST_DIR}/*.cpp
  ${CMAKE_CURRENT_LIST_DIR}/ui/*.h
  ${CMAKE_CURRENT_LIST_DIR}/ui/*.cpp
  ${CMAKE_CURRENT_LIST_DIR}/assets/fonts/*.h
  ${CMAKE_CURRENT_LIST_DIR}/assets/fonts/*.cpp
  ${CMAKE_CURRENT_LIST_DIR}/assets/backgrounds/*.h
  ${CMAKE_CURRENT_LIST_DIR}/assets/backgrounds/*.cpp)

hello_imgui_add_app(bb_text_extractor ${sources_bb_text_extractor}
                    ASSETS_LOCATION ${temp_assets_dir})

target_link_libraries(bb_text_extractor PUBLIC imgui_utilities source_parse
                                               text_extractor_core glfw)
target_include_directories(
  bb_text_extractor
  PUBLIC ${GLFW3_INCLUDE_DIRS} ${textedit_dir} ${fplus_dir}
         ${imgui_markdown_dir} ${GLFW3_LIBRARIES} ${OPENGL_LIBRARIES})

function(_hello_imgui_add_windows_icon app_name ico_location)
  if(NOT EXISTS ${ico_location})
    return()
  endif()

  # Create rc file
  set(icon_rc_file "${CMAKE_CURRENT_BINARY_DIR}/app_${app_name}.rc")
  set(icon_rc_file_contents "IDI_ICON1 ICON DISCARDABLE \"${ico_location}\"")
  file(WRITE ${icon_rc_file} ${icon_rc_file_contents})

  # Add the rc file to the executable
  target_sources(${app_name} PRIVATE ${icon_rc_file})
endfunction()
if(WIN32)
  _hello_imgui_add_windows_icon(bb_text_extractor ${assets_dir}/favicon.ico)
endif()

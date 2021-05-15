
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_EXECUTABLE_SUFFIX ".html")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY, "built/")

set(CMAKE_CXX_FLAGS "-I\"/usr/local/Cellar/glm/0.9.9.8/include/\" -Wall -Wformat -s USE_SDL=2 -s WASM=1 -std=c++17 -g3 -fsanitize=address -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s FULL_ES3=1 -s FULL_ES2=1 -s USE_GLFW=1 -s GL_PREINITIALIZED_CONTEXT=1 -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=1 -s NO_EXIT_RUNTIME=0 -s ASSERTIONS=1 --pre-js ../shell-files/create-context.js --no-heap-copy --preload-file ../shaders --preload-file ../imgui/misc/fonts/ --shell-file ../shell-files/shell_minimal.html")

project(sphere-go LANGUAGES CXX)

file(COPY shaders DESTINATION ".")

add_executable(main
  src/main.c++
  src/normals/normals.c++
  src/sphere/sphere.c++
  src/dialogs/dialogs.c++  
  imgui/imgui_impl_sdl.cpp
  imgui/imgui_impl_opengl3.cpp
  imgui/imgui.cpp
  imgui/imgui_demo.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_widgets.cpp
)

set_target_properties(
  main
  PROPERTIES
    OUTPUT_NAME "main"
    SUFFIX ".html"
)


configure_file(server/Server.py Server.py COPYONLY)

#include "dialogs.h++"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_sdl.h"
#include "../../imgui/imgui_impl_opengl3.h"

extern "C" {
SDL_Window* dialogs::initImgui() {
  SDL_Window * window;
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    
    window = SDL_CreateWindow("spheres webgl demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);

    
    g_GLContext = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);

    // Begin imgui add
    if (!g_GLContext)
    {
      // fprintf(stderr, "Failed to initialize WebGL context!\n");
    }
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGui_ImplSDL2_InitForOpenGL(window, g_GLContext);
    ImGui_ImplOpenGL3_Init("#version 100");
    // end an imgui add
    return window;
}
}

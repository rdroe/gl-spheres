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
  
  ImGuiIO& dialogs::getIo () {
    return ImGui::GetIO();
  }

  void dialogs::compose(SDL_Window* window) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    if (show_demo_window) {
      ImGui::ShowDemoWindow(&show_demo_window);
    }

    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!");             
      ImGui::Text("This is some useful text.");   
      ImGui::Checkbox("Demo Window", &show_demo_window);
      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

      if (ImGui::Button("Button"))                  // Buttons return true when clicked
      { counter++;

      }

      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
    }

    if (show_another_window)
    {
      ImGui::Begin("Another Window", &show_another_window);
      ImGui::Text("Hello from another window!");
      if (ImGui::Button("Close Me")){
        show_another_window = false;
      }
      ImGui::End();
    }
  }

  void dialogs::render () {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  };
}

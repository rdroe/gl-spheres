#include "dialogs.h++"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_opengl3.h"
#include "../../imgui/imgui_impl_sdl.h"

const float INIT_FRAMERATE = 1000.0F;

extern "C" {

SDL_Window *dialogs::initImgui() {
  SDL_Window *window;
  uint wf =
      (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

  SDL_WindowFlags window_flags = (SDL_WindowFlags)wf;

  window =
      SDL_CreateWindow("spheres webgl demo", (uint)SDL_WINDOWPOS_CENTERED,
                       (uint)SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);

  g_GLContext = SDL_GL_CreateContext(window);
  SDL_GL_SetSwapInterval(1);

  // Begin imgui add
  if (g_GLContext == nullptr) {
    // fprintf(stderr, "Failed to initialize WebGL context!\n");
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext(nullptr);

  ImGui_ImplSDL2_InitForOpenGL(window, g_GLContext);
  ImGui_ImplOpenGL3_Init("#version 100");
  // end an imgui add
  return window;
}

ImGuiIO &dialogs::getIo() { return ImGui::GetIO(); }

void dialogs::compose(SDL_Window *window) {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
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
    static float f = 0.0F;
    static int counter = 0;

    ImGui::Begin("Hello, world!", nullptr, 0); // NOLINT hicpp-vararg
    ImGui::Text("This is some useful text.");  // NOLINT hicpp-vararg
    ImGui::Checkbox("Demo Window", &show_demo_window);
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0F, 1.0F, "%.3f", 1);

    if (ImGui::Button("Button",
                      ImVec2(0, 0))) // Buttons return true when clicked
    {
      counter++;
    }

    ImGui::SameLine(0, 1);
    ImGui::Text("counter = %d", counter); // NOLINT hicpp-vararg

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                INIT_FRAMERATE / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate); // NOLINT hicpp-vararg
    ImGui::End();
  }

  if (show_another_window) {
    ImGui::Begin("Another Window", &show_another_window, 0);
    ImGui::Text("Hello from another window!"); // NOLINT hicpp-vararg
    if (ImGui::Button("Close Me", ImVec2(0, 0))) {
      show_another_window = false;
    }
    ImGui::End();
  }
}

void dialogs::render() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
};
}

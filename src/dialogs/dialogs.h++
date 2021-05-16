
#ifndef dialogs_h
#define dialogs_h

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_opengl3.h"
#include "../../imgui/imgui_impl_sdl.h"
#include <SDL2/SDL.h>

extern "C" {
class dialogs {
  SDL_GLContext g_GLContext = NULL;
  bool show_demo_window = true;
  bool show_another_window = false;

public:
  SDL_Window *initImgui();
  ImGuiIO &getIo();
  void compose(SDL_Window *window);
  void render();
};
}
#endif

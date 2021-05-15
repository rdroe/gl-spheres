
#ifndef dialogs_h
    #define dialogs_h

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_sdl.h"
#include "../../imgui/imgui_impl_opengl3.h"
#include <SDL2/SDL.h>

extern "C" {
  class dialogs {
    SDL_GLContext g_GLContext = NULL;
    bool show_demo_window;
    bool show_another_window;    
    public:
      SDL_Window* initImgui();
      ImGuiIO& getIo();
      void compose(SDL_Window* window);
      void render();
    
      dialogs() {
	show_demo_window = true;
	show_another_window = false;
      }
    
  };
}
#endif

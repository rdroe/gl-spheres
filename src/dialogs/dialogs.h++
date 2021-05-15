
#ifndef dialogs_h
    #define dialogs_h

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_sdl.h"
#include "../../imgui/imgui_impl_opengl3.h"
#include <SDL2/SDL.h>

extern "C" {
  class dialogs {
    SDL_GLContext g_GLContext = NULL;
    public:
      SDL_Window* initImgui();
    
      dialogs() {}
    
  };
}
#endif

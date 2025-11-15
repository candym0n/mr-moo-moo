#ifndef __SCREEN_SAVER_H__
#define __SCREEN_SAVER_H__

#define WIN32_LEAN_AND_MEAN

#include <SDL3/SDL.h>
#include <windows.h>

class ScreenSaver {
public:
    ScreenSaver(HWND hwnd); // Creates full screen window OR uses existing window

    SDL_AppResult HandleEvent(SDL_Event* event);
    SDL_AppResult UpdateFrame();

private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

    int m_Width, m_Height;

    int CreateWindowAndRenderer(HWND hwnd);
};

#endif // __SCREEN_SAVER_H__

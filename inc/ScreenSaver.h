#ifndef __SCREEN_SAVER_H__
#define __SCREEN_SAVER_H__

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <SDL3/SDL.h>

#include <Cow.h>

class ScreenSaver {
public:
    // Non-copyable, non-movable
    ScreenSaver(const ScreenSaver&) = delete;
    ScreenSaver& operator=(const ScreenSaver&) = delete;

    explicit ScreenSaver(HWND hwnd);
    ~ScreenSaver();

    SDL_AppResult HandleEvent(const SDL_Event* event);
    SDL_AppResult UpdateFrame();

    bool IsValid() const noexcept { return m_Valid; }

private:
    Cow* m_Cow;

    uint64_t m_LastTime;

    bool m_Valid = false;
    SDL_Window* m_Window = nullptr;
    SDL_Renderer* m_Renderer = nullptr;
    int m_Width = 0, m_Height = 0;

    int CreateWindowAndRenderer(HWND hwnd);
    void Cleanup() noexcept;
};

#endif // __SCREEN_SAVER_H__

#ifndef SCREEN_SAVER_H
#define SCREEN_SAVER_H

#define WIN32_LEAN_AND_MEAN

#include <memory>

#include <windows.h>
#include <SDL3/SDL.h>

#include <Config.h>
#include <ScenePlayer.h>

#define CONFIG_FILE_PATH "C:/Users/Jayden/AppData/Local/MrMooMoo/config.xml"

class ScreenSaver {
    using SDLWindowPtr = std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>;
    using SDLRendererPtr = std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>;

public:
    // Non-copyable, non-movable
    ScreenSaver(const ScreenSaver&) = delete;
    ScreenSaver& operator=(const ScreenSaver&) = delete;

    explicit ScreenSaver(HWND hwnd);
    ~ScreenSaver() = default;

    SDL_AppResult HandleEvent(const SDL_Event* event);
    SDL_AppResult UpdateFrame();

    bool IsValid() const noexcept { return m_Valid; }

private:
    uint64_t m_LastTime;

    bool m_Valid = false;
    SDLWindowPtr m_Window ;
    std::shared_ptr<SDL_Renderer> m_Renderer;
    int m_Width = 0, m_Height = 0;

    std::unique_ptr<ScenePlayer> m_ScenePlayer;
    std::unique_ptr<Config> m_Config;
    //SDLRendererPtr m_Renderer;

    int CreateWindowAndRenderer(HWND hwnd);
};

#endif // SCREEN_SAVER_H

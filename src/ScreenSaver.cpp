#include <ScreenSaver.h>

// Not the sky background, only for overshoots
#define OVERSHOOT_BG_R 0
#define OVERSHOOT_BG_G 0
#define OVERSHOOT_BG_B 0

ScreenSaver::ScreenSaver(HWND hwnd) : 
    m_LastTime(SDL_GetPerformanceCounter()),
    m_Window(nullptr, [](SDL_Window* win){ if(win) SDL_DestroyWindow(win); })
{
    m_Valid = (CreateWindowAndRenderer(hwnd) == 0);

    if (!m_Valid)
        return;
    
    SDL_SetRenderLogicalPresentation(m_Renderer.get(), LOGICAL_WIDTH, LOGICAL_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    m_ScenePlayer = std::make_unique<ScenePlayer>();
    m_Config = std::make_unique<Config>(HelperFunctions::GetAssetPath("config.xml"), m_Renderer);

    m_ScenePlayer->SetBackgroundTexture(m_Config->GetBackgroundTexture());
    m_ScenePlayer->SetScenes(
        m_Config->GetScenes(),
        m_Config->GetSceneWeights(),
        m_Config->GetSceneShortcuts(),
        m_Config->GetIdleSceneIndex()
    );
}

int ScreenSaver::CreateWindowAndRenderer(HWND hwnd) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_SetAppMetadata("Mr. Moo Moo", "1.0", "com.mr.moomoo");

    // The custom deleter implementation
    auto windowDeleter = [](SDL_Window* win) { if (win) SDL_DestroyWindow(win); };

    // When assigning, use std::move:
    if (!hwnd) {
        auto tempWindow = SDLWindowPtr(
            SDL_CreateWindow("Screen Saver", 0, 0, SDL_WINDOW_FULLSCREEN),
            windowDeleter
        );
        m_Window = std::move(tempWindow);
    } else {
        SDL_PropertiesID props = SDL_CreateProperties();
        SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, hwnd);
        auto tempWindow = SDLWindowPtr(
            SDL_CreateWindowWithProperties(props),
            windowDeleter
        );
        m_Window = std::move(tempWindow);
        SDL_DestroyProperties(props);
    }

    if (!m_Window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        return 1;
    }

    m_Renderer = SDLRendererPtr(
        SDL_CreateRenderer(m_Window.get(), nullptr),
        SDL_DestroyRenderer
    );
    if (!m_Renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        return 1;
    }

    SDL_GetWindowSize(m_Window.get(), &m_Width, &m_Height);
    return 0;
}

SDL_AppResult ScreenSaver::HandleEvent(const SDL_Event* event) {
    if (!event) return SDL_APP_CONTINUE;

    switch (event->type) {
    case SDL_EVENT_QUIT:
        // Ignore normal quit events; only Shift+Escape should quit.
        return SDL_APP_CONTINUE;

    case SDL_EVENT_KEY_DOWN: {
        const SDL_KeyboardEvent &ke = event->key;

        // Check for Shift + Escape to quit
        if ((ke.mod & SDL_KMOD_SHIFT) && ke.key == SDLK_ESCAPE) { // [web:1][web:8][web:19]
            return SDL_APP_SUCCESS; // [web:6][web:9][web:12][web:15][web:18]
        }

        // For other keys, check for shortcut
        SDL_Keycode keycode = ke.key; // key field in SDL3 keyboard event [web:17]
        
        int sceneIndex = m_ScenePlayer->GetSceneFromShortcut(static_cast<char>(keycode));
        if (sceneIndex >= 0) {
            m_ScenePlayer->SetQueueScene(sceneIndex);
        }

        return SDL_APP_CONTINUE;
    }

    default:
        return SDL_APP_CONTINUE;
    }
}


SDL_AppResult ScreenSaver::UpdateFrame() {
    if (!m_Renderer) return SDL_APP_FAILURE;

    // Calculate delta time
    uint64_t currentTime = SDL_GetPerformanceCounter();
    double deltaTime = static_cast<double>(currentTime - m_LastTime) / SDL_GetPerformanceFrequency();
    m_LastTime = currentTime;

    // Update the scene
    m_ScenePlayer->Update(deltaTime);

    // Draw the scene
    SDL_SetRenderDrawColor(m_Renderer.get(), OVERSHOOT_BG_R, OVERSHOOT_BG_G, OVERSHOOT_BG_B, 255);
    SDL_RenderClear(m_Renderer.get());
    m_ScenePlayer->Draw(m_Renderer);
    SDL_RenderPresent(m_Renderer.get());
    return SDL_APP_CONTINUE;
}

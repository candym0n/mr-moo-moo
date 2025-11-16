#include "ScreenSaver.h"

ScreenSaver::ScreenSaver(HWND hwnd) : 
    m_LastTime(SDL_GetPerformanceCounter())
{
    m_Valid = (CreateWindowAndRenderer(hwnd) == 0);

    if (!m_Valid)
        return;

    m_Cow = new Cow(m_Renderer);
}

ScreenSaver::~ScreenSaver() {
    Cleanup();
}

void ScreenSaver::Cleanup() noexcept {
    if (m_Renderer) {
        SDL_DestroyRenderer(m_Renderer);
        m_Renderer = nullptr;
    }

    if (m_Window) {
        SDL_DestroyWindow(m_Window);
        m_Window = nullptr;
    }
}

int ScreenSaver::CreateWindowAndRenderer(HWND hwnd) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_SetAppMetadata("Mr. Moo Moo", "1.0", "com.mr.moomoo");

    if (!hwnd) {
        m_Window = SDL_CreateWindow("Screen Saver", 0, 0, SDL_WINDOW_FULLSCREEN);
    } else {
        SDL_PropertiesID props = SDL_CreateProperties();
        SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, hwnd);
        m_Window = SDL_CreateWindowWithProperties(props);
        SDL_DestroyProperties(props);
    }

    if (!m_Window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        return 1;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, nullptr);
    if (!m_Renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        return 1;
    }

    SDL_GetWindowSize(m_Window, &m_Width, &m_Height);
    return 0;
}

SDL_AppResult ScreenSaver::HandleEvent(const SDL_Event* event) {
    if (!event) return SDL_APP_CONTINUE;
    switch (event->type) {
        case SDL_EVENT_QUIT:
        case SDL_EVENT_KEY_DOWN:
            return SDL_APP_SUCCESS;
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
 
    // Update everything
    m_Cow->Update(deltaTime);

    // Draw everything
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_Renderer);
    m_Cow->Render(m_Renderer);
    SDL_RenderPresent(m_Renderer);
    return SDL_APP_CONTINUE;
}

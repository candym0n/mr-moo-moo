#include <ScreenSaver.h>



// Not the sky background, only for overshoots
#define OVERSHOOT_BG_R 135
#define OVERSHOOT_BG_G 206
#define OVERSHOOT_BG_B 235

ScreenSaver::ScreenSaver(HWND hwnd) : 
    m_LastTime(SDL_GetPerformanceCounter())
{
    m_Valid = (CreateWindowAndRenderer(hwnd) == 0);

    SDL_SetRenderLogicalPresentation(m_Renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    if (!m_Valid)
        return;
    
    m_Scene = new ScenePlayer();
    m_Config = new Config(CONFIG_PATH, m_Renderer);

    m_Scene->SetBackgroundTexture(m_Config->getBackgroundTexture());
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

    // Update the scene
    m_Scene->Update(deltaTime);

    // Draw the scene
    SDL_SetRenderDrawColor(m_Renderer, OVERSHOOT_BG_R, OVERSHOOT_BG_G, OVERSHOOT_BG_B, 255);
    SDL_RenderClear(m_Renderer);
    m_Scene->Draw(m_Renderer);
    SDL_RenderPresent(m_Renderer);
    return SDL_APP_CONTINUE;
}

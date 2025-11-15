#include <ScreenSaver.h>

ScreenSaver::ScreenSaver(HWND hwnd)
    : m_Window(nullptr), m_Renderer(nullptr), m_Width(0), m_Height(0)
{
    if (CreateWindowAndRenderer(hwnd) != 0) {
        SDL_Log("Failed to create window and renderer for screen saver.");
    }
}

SDL_AppResult ScreenSaver::HandleEvent(SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_KEY_DOWN) {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult ScreenSaver::UpdateFrame()
{
    // Clear the screen with a black color
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_Renderer);

    // Present the backbuffer
    SDL_RenderPresent(m_Renderer);

    return SDL_APP_CONTINUE;
}

int ScreenSaver::CreateWindowAndRenderer(HWND hwnd)
{
    SDL_SetAppMetadata("Mr. Moo Moo", "1.0", "com.mr.moomoo");

    // Initialize SDL video subsystem
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    if (hwnd == nullptr) { // Make our window FROM SCRATCH
        m_Window = SDL_CreateWindow("Screen Saver", 0, 0, SDL_WINDOW_FULLSCREEN);
    } else { // Create it from HWND reference
        SDL_PropertiesID props = SDL_CreateProperties();
        SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, hwnd);

        m_Window = SDL_CreateWindowWithProperties(props);

        // Clean up properties if necessary
        SDL_DestroyProperties(props);
    }

    if (!m_Window) {
        SDL_Log("Unable to create SDL Window: %s", SDL_GetError());
        return 1;
    }

    // Create the renderer
    m_Renderer = SDL_CreateRenderer(m_Window, nullptr);

    if (!m_Renderer) {
        SDL_Log("Unable to create SDL Renderer: %s", SDL_GetError());
        return 1;
    }

    return 0; // Yipee!
}



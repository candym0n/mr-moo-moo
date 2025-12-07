#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */

#include <ScreenSaver.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define TARGET_FPS        30
#define TARGET_FRAME_TIME_MS (1000 / TARGET_FPS)

/* Optional: store timing data in appstate, or use static variables */
struct AppState {
    ScreenSaver* screenSaver;
    Uint64 last_frame_start_ms;
};

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    srand(time(nullptr));

    HelperFunctions::GenerateAssetDirPath();

    AppState* state = new AppState{};
    state->screenSaver = new ScreenSaver(nullptr);
    state->last_frame_start_ms = SDL_GetTicks();  /* initial value */

    *appstate = static_cast<void*>(state);

    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    AppState* state = static_cast<AppState*>(appstate);
    return state->screenSaver->HandleEvent(event);
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    AppState* state = static_cast<AppState*>(appstate);

    Uint64 frame_start = SDL_GetTicks();
    Uint64 frame_elapsed = frame_start - state->last_frame_start_ms;

    /* Update and render one frame */
    SDL_AppResult result = state->screenSaver->UpdateFrame();
    if (result != SDL_APP_CONTINUE) {
        return result;
    }

    /* Simple frame cap */
    if (frame_elapsed < TARGET_FRAME_TIME_MS) {
        SDL_Delay((Uint32)(TARGET_FRAME_TIME_MS - frame_elapsed));
    }

    state->last_frame_start_ms = frame_start;

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    AppState* state = static_cast<AppState*>(appstate);
    delete state->screenSaver;
    delete state;
}

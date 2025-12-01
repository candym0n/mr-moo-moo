#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */

#include <ScreenSaver.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    srand(time(nullptr));

    ScreenSaver* screenSaver = new ScreenSaver(nullptr);

    *appstate = static_cast<void*>(screenSaver);

    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    // Get the screen saver from appstate
    ScreenSaver* screenSaver = static_cast<ScreenSaver*>(appstate);

    // Let screenSaver do all the heavy lifting
    return screenSaver->HandleEvent(event);
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    // Get the screen saver from appstate
    ScreenSaver* screenSaver = static_cast<ScreenSaver*>(appstate);

    // Let screenSaver do all the heavy lifting
    return screenSaver->UpdateFrame();
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. Thank you, SDL.*/
    delete static_cast<ScreenSaver*>(appstate);
}

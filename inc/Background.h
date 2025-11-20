#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include <SDL3/SDL.h>

#include <Camera.h>

class Background {
public:
    Background();

    // Set the background texture. Does not take ownership of the texture.
    void SetTexture(SDL_Texture* texture);

    // Draws the background texture to the renderer.
    void Draw(SDL_Renderer* renderer, Camera* camera) const;

private:
    SDL_Texture* m_Texture;
};

#endif // __BACKGROUND_H__

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <memory>

#include <SDL3/SDL.h>

#include <Camera.h>

class Background {
public:
    Background();

    // Set the background texture. Does not take ownership of the texture.
    void SetTexture(std::shared_ptr<SDL_Texture> texture);

    // Draws the background texture to the renderer.
    void Draw(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Camera> camera) const;

private:
    std::shared_ptr<SDL_Texture> m_Texture;
};

#endif // BACKGROUND_H

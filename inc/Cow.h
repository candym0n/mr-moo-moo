#ifndef __COW_H__
#define __COW_H__

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <Animation.h>

class Cow {
public:
    Cow(SDL_Renderer* renderer);
    ~Cow();

    void Update(double dt);

    void Render(SDL_Renderer* renderer) const;

private:
    Animation* m_Animation; // Draws the cow and all its glory
    
    SDL_Texture* m_WalkingTexture;
    SDL_Texture* m_EatingTexture;
    SDL_Texture* m_TurningTexture;
};

#endif // __COW_H__

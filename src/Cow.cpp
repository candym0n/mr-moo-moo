#include <Cow.h>

#include <AssetHelper.h>

#include <cstdio>

float x = 0;

Cow::Cow(SDL_Renderer* renderer)
{
    // Load all the texture goodies
    m_TurningTexture = AssetHelper::LoadTexture(renderer, "images/cow/cow_turn.png");
    m_WalkingTexture = AssetHelper::LoadTexture(renderer, "images/cow/cow_walk.png");
    m_EatingTexture = AssetHelper::LoadTexture(renderer, "images/cow/cow_eat.png");

    // Initialize the animation
    m_Animation = new Animation(m_WalkingTexture, 128, 128, 0.25, 4, 7);
    m_Animation->Play();
}

void Cow::Update(double dt)
{
    m_Animation->Update(dt);
}

void Cow::Render(SDL_Renderer *renderer) const
{
    m_Animation->Render(renderer, x, 100, 512, 512);

    x += 0.1;
}

Cow::~Cow() {
    delete m_Animation;
    SDL_DestroyTexture(m_WalkingTexture);
    SDL_DestroyTexture(m_EatingTexture);
    SDL_DestroyTexture(m_TurningTexture);
}


#include "ScenePlayer.h"

ScenePlayer::ScenePlayer()
{
    m_Background = new Background();
    m_Camera = new Camera(0);
}

void ScenePlayer::SetBackgroundTexture(SDL_Texture *bg)
{
    m_Background->SetTexture(bg);
}

void ScenePlayer::Draw(SDL_Renderer *renderer)
{
    m_Background->Draw(renderer, m_Camera);
}

void ScenePlayer::Update(double deltaTime)
{
    m_Camera->moveX(-1);
}

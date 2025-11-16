#include "Animation.h"
#include <cassert>

Animation::Animation(SDL_Texture* texture, float frameWidth, float frameHeight, float frameDuration, int start, int end)
    : m_Texture(nullptr), m_FrameWidth(0), m_FrameHeight(0), m_Columns(0), m_Rows(0),
      m_FrameDuration(0), m_StartFrame(0), m_EndFrame(0), m_CurrentFrame(0),
      m_ElapsedTime(0.0f), m_Playing(false)
{
    SetTexture(texture, frameWidth, frameHeight, frameDuration, start, end);
}

void Animation::SetTexture(SDL_Texture* texture, float frameWidth, float frameHeight, float frameDuration, int start, int end)
{
    assert(texture && "Texture must not be null");
 
    float textureWidth, textureHeight;
    SDL_GetTextureSize(texture, &textureWidth, &textureHeight);
 
    m_Texture = texture;
    m_FrameWidth = frameWidth;
    m_FrameHeight = frameHeight;
    m_FrameDuration = frameDuration;
    
    m_Columns = static_cast<int>(textureWidth / frameWidth);
    m_Rows = static_cast<int>(textureHeight / frameHeight);

    m_StartFrame = start;
    m_EndFrame = end > start ? end : m_Columns * m_Rows - 1;
    m_CurrentFrame = start;
    m_ElapsedTime = 0.0f;
    m_Playing = false;
}

void Animation::Play(bool play)
{
    m_Playing = play;
}

void Animation::Pause()
{
    m_Playing = false;
}

void Animation::Update(double dt)
{
    if (!m_Playing || m_FrameDuration <= 0) return;

    m_ElapsedTime += dt;
    while (m_ElapsedTime >= m_FrameDuration)
    {
        m_ElapsedTime -= m_FrameDuration;
        if (m_CurrentFrame >= m_EndFrame)
            m_CurrentFrame = m_StartFrame;
        else
            ++m_CurrentFrame;
    }
}

void Animation::Render(SDL_Renderer* renderer, int x, int y, int w, int h) const
{
    if (!m_Texture) return;
    int col = m_CurrentFrame % m_Columns;
    int row = m_CurrentFrame / m_Columns;

    SDL_FRect srcRect = {
        static_cast<float>(col * m_FrameWidth),
        static_cast<float>(row * m_FrameHeight),
        static_cast<float>(m_FrameWidth),
        static_cast<float>(m_FrameHeight)
    };

    SDL_FRect dstRect = {
        static_cast<float>(x),
        static_cast<float>(y),
        static_cast<float>(w),
        static_cast<float>(h)
    };

    SDL_RenderTexture(renderer, m_Texture, &srcRect, &dstRect);
}

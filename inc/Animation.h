#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL3/SDL.h>

#include <Camera.h>

/**
 * @brief Handles frame-based animation from a sprite sheet.
 *
 * Frames are indexed left-to-right, top-down. Frame index is x + columns * y.
 */
class Animation
{
public:
    Animation();

    void SetTexture(SDL_Texture* texture, float frameWidth, float frameHeight, float frameDuration, int start = 0, int end = 0);

    void Play(bool play = true);
    void Pause();

    void Update(double dt);
    void Render(SDL_Renderer* renderer, Camera* camera,int x, int y, int w, int h) const;

    bool IsPlaying() const { return m_Playing; }
    int GetFrame() const { return m_CurrentFrame; }

private:
    SDL_Texture* m_Texture;
    float m_FrameWidth, m_FrameHeight;
    int m_Columns, m_Rows;
    float m_FrameDuration;

    int m_StartFrame, m_EndFrame, m_CurrentFrame;
    float m_ElapsedTime;
    bool m_Playing;
};

#endif // ANIMATION_H

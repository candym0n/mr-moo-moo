#include <Background.h>

Background::Background()
    : m_Texture(nullptr) {}

void Background::SetTexture(SDL_Texture* texture) {
    m_Texture = texture;
}

void Background::Draw(SDL_Renderer* renderer, Camera* camera) const
{
    if (!m_Texture) return;

    float width, height;

    SDL_GetTextureSize(m_Texture, &width, &height);

    SDL_FRect dstRect = {
        static_cast<float>(-LOGICAL_WIDTH - camera->getX()),
        0,
        width,
        height
    };

    SDL_RenderTexture(renderer, m_Texture, nullptr, &dstRect);
}

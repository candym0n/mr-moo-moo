#include <Background.h>

Background::Background()
    : m_Texture(nullptr) {}

void Background::SetTexture(std::shared_ptr<SDL_Texture> texture) {
    m_Texture = texture;
}

void Background::Draw(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Camera> camera) const
{
    if (!m_Texture) return;

    float width, height;

    SDL_GetTextureSize(m_Texture.get(), &width, &height);

    SDL_FRect dstRect = {
        static_cast<float>(-LOGICAL_WIDTH - camera->getX()),
        0,
        width,
        height
    };

    SDL_RenderTexture(renderer.get(), m_Texture.get(), nullptr, &dstRect);
}

#include "AssetHelper.h"
#include <iostream>

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> AssetHelper::m_ImageCache{};

std::string AssetHelper::AssetDirPath() {
    return "C:/Users/Jayden/AppData/Local/MrMooMoo/";
}

std::string AssetHelper::GetAssetPath(const std::string& path) {
    return AssetDirPath() + path;
}

std::shared_ptr<SDL_Texture> AssetHelper::LoadTexture(std::shared_ptr<SDL_Renderer> renderer, const std::string& path)
{
    auto it = m_ImageCache.find(path);
    if (it != m_ImageCache.end())
        return it->second;

    SDL_Texture* raw = IMG_LoadTexture(renderer.get(), GetAssetPath(path).c_str());
    if (!raw) {
        std::cerr << "Failed to load texture '" << path << "': " << SDL_GetError() << '\n';
        return nullptr;
    }

    SDL_SetTextureScaleMode(raw, SDL_SCALEMODE_NEAREST);

    // Use a custom deleter so SDL_DestroyTexture is called automatically
    auto texturePtr = std::shared_ptr<SDL_Texture>(raw, SDL_DestroyTexture);
    m_ImageCache[path] = texturePtr;
    return texturePtr;
}

void AssetHelper::Clear()
{
    m_ImageCache.clear();
}

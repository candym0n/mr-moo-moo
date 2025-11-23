#ifndef ASSET_HELPER_H
#define ASSET_HELPER_H

#include <string>
#include <unordered_map>
#include <memory>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class AssetHelper {
public:

    // Loads a texture from an asset path (returns a shared pointer for safe ownership)
    static std::shared_ptr<SDL_Texture> LoadTexture(std::shared_ptr<SDL_Renderer> renderer, const std::string& path);

    // Clears all cached textures (releases memory)
    static void Clear();

private:
    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> m_ImageCache;
    static std::string AssetDirPath();
    
    // Retrieves the full asset path
    static std::string GetAssetPath(const std::string& path);
};

#endif // ASSET_HELPER_H

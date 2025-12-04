#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <string>
#include <sstream>
#include <unordered_map>
#include <memory>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class HelperFunctions {
public:
    // Establish the asset directory path
    static void GenerateAssetDirPath();

    // Loads a texture from an asset path (returns a shared pointer for safe ownership)
    static std::shared_ptr<SDL_Texture> LoadTexture(std::shared_ptr<SDL_Renderer> renderer, const std::string& path);

    // Clears all cached textures (releases memory)
    static void ClearTextureCache();

    // Parses either a number or "random min max" into a float (e.g. "-100", "100", "random -50 50")
    static float ParseNumberOrRandom(const std::string& input);

    // Retrieves the full asset path
    static std::string GetAssetPath(const std::string& path);

private:
    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> m_ImageCache;
    static std::string AssetDirPath();
    
    

    static std::string m_AssetDirPath;
};

#endif // HELPER_FUNCTIONS_H

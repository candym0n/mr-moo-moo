#include "HelperFunctions.h"
#include <iostream>

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> HelperFunctions::m_ImageCache{};

std::string HelperFunctions::AssetDirPath() {
    return "C:/Users/Jayden/AppData/Local/MrMooMoo/";
}

std::string HelperFunctions::GetAssetPath(const std::string& path) {
    return AssetDirPath() + path;
}

std::shared_ptr<SDL_Texture> HelperFunctions::LoadTexture(std::shared_ptr<SDL_Renderer> renderer, const std::string& path)
{
    auto it = m_ImageCache.find(path);
    if (it != m_ImageCache.end())
        return it->second;

    if (!renderer)
        printf("Renderer is null when trying to load texture '%s'\n", path.c_str());

    std::string fullPath = GetAssetPath(path);

    SDL_Texture* raw = IMG_LoadTexture(renderer.get(), fullPath.c_str());
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

void HelperFunctions::ClearTextureCache()
{
    m_ImageCache.clear();
}

float HelperFunctions::ParseNumberOrRandom(const std::string &input)
{
    std::istringstream iss(input);
    std::string token;
    iss >> token;

    if (token == "random") {
        float min, max;
        iss >> min >> max;
        if (iss.fail()) {
            throw std::invalid_argument("Invalid random range: " + input);
        }
        float randomValue = min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
        return randomValue;
    } else {
        try {
            return std::stof(token);
        } catch (const std::exception&) {
            throw std::invalid_argument("Invalid number: " + input);
        }
    }
}

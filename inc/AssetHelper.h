#ifndef __ASSET_HELPER_H__
#define __ASSET_HELPER_H__

#include <string>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

const std::string ASSET_DIR_PATH = "C:/Users/Jayden/AppData/Local/MrMooMoo/";

class AssetHelper {
public:
    static std::string GetAssetPath(std::string path);
    static SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path);
};

#endif // __ASSET_HELPER_H__

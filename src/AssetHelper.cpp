#include <AssetHelper.h>

std::string AssetHelper::GetAssetPath(std::string path)
{
    return ASSET_DIR_PATH + path;
}

SDL_Texture* AssetHelper::LoadTexture(SDL_Renderer* renderer, std::string path)
{
    auto result = IMG_LoadTexture(renderer, AssetHelper::GetAssetPath(path).c_str());

    if (result == NULL)
        printf("Failed to load texture: %s\n", SDL_GetError());

    SDL_SetTextureScaleMode(result, SDL_SCALEMODE_NEAREST);

    return result;
}

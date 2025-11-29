#ifndef SCENE_PLAYER_H
#define SCENE_PLAYER_H

#include <memory>

#include <SDL3/SDL.h>

#include <HelperFunctions.h>
#include <Animation.h>
#include <Background.h>
#include <Camera.h>

class ScenePlayer {
public:
    ScenePlayer();
    ~ScenePlayer();

    void SetBackgroundTexture(std::shared_ptr<SDL_Texture> bg);

    void CheatInit(std::shared_ptr<SDL_Renderer> renderer);

    void Draw(std::shared_ptr<SDL_Renderer> renderer);
    void Update(double deltaTime);

private:
    std::shared_ptr<Camera> m_Camera;
    std::unique_ptr<Background> m_Background;
    
    // Ignore my cheats for demonstration purposes
    std::unique_ptr<Animation> m_Cow;
    std::shared_ptr<SDL_Texture> m_Walking;

    void walkRight();
    void standStill();
    void walkLeft();
};

#endif // SCENE_PLAYER_H

#ifndef SCENE_PLAYER_H
#define SCENE_PLAYER_H

#include <memory>
#include <vector>

#include <SDL3/SDL.h>

#include <Actor.h>
#include <Animation.h>
#include <Background.h>
#include <Camera.h>
#include <HelperFunctions.h>
#include <Scene.h>

class ScenePlayer {
public:
    ScenePlayer();
    ~ScenePlayer() = default;

    void SetBackgroundTexture(std::shared_ptr<SDL_Texture> bg);

    void SetScene(std::string id);

    void SetScenes(std::map<std::string, std::shared_ptr<Scene>> scenes);

    void Draw(std::shared_ptr<SDL_Renderer> renderer);
    void Update(double deltaTime);

private:
    std::shared_ptr<Camera> m_Camera;
    std::unique_ptr<Background> m_Background;

    std::map<std::string, std::shared_ptr<Scene>> m_Scenes;
    std::shared_ptr<Scene> m_Scene;
};

#endif // SCENE_PLAYER_H

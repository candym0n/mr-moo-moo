#ifndef SCENE_PLAYER_H
#define SCENE_PLAYER_H

#include <memory>
#include <vector>
#include <numeric>

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

    void SetScenes(std::vector<std::shared_ptr<Scene>> scenes, std::vector<int> weights, int idleScene);

    void Draw(std::shared_ptr<SDL_Renderer> renderer);
    void Update(double deltaTime);

    int GetRandomSceneIndex() const;

private:
    std::shared_ptr<Camera> m_Camera;
    std::unique_ptr<Background> m_Background;

    std::vector<std::shared_ptr<Scene>> m_Scenes;
    std::shared_ptr<Scene> m_Scene;

    std::vector<int> m_SceneWeights;
    int m_TotalWeight;    

    int m_IdleScene;
};

#endif // SCENE_PLAYER_H

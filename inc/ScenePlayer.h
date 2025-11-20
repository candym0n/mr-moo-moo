#ifndef __SCENE_PLAYER_H__
#define __SCENE_PLAYER_H__

#include <SDL3/SDL.h>

#include <Camera.h>
#include <Background.h>

class ScenePlayer {
public:
    ScenePlayer();
    ~ScenePlayer();

    void SetBackgroundTexture(SDL_Texture* bg);

    void Draw(SDL_Renderer* renderer);
    void Update(double deltaTime);

private:
    Camera* m_Camera;
    Background* m_Background;
};

#endif // __SCENE_PLAYER_H__

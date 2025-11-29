#ifndef ACTOR_H
#define ACTOR_H

#include <memory>
#include <string>
#include <vector>

#include <SDL3/SDL.h>

#include <Animation.h>
#include <functional/Functional.h>
#include <functional/FunctionalFactory.h>

class Functional;
struct FunctionalCreationArgs;

class Actor {
public:
    Actor(std::string id, int width, int height);

    void RegisterFunctional(std::string& type, FunctionalCreationArgs arguments);
    void IncludeAnimation(std::string& id, std::shared_ptr<SDL_Texture> sheet, float frameWidth, float frameHeight, float frameDuration, int start, int end);
    void SetCurrentAnimation(std::string& id);

    void Update(double deltaTime);
    void Draw(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Camera> camera);

    void SetPosition(float x, float y);
    void MoveBy(float dx, float dy);

    float GetX() const { return m_X; }
    float GetY() const { return m_Y; }

    std::string GetId();
private:
    std::string m_Id;
    std::shared_ptr<Animation> m_CurrentAnimation;
    std::map<std::string, std::shared_ptr<Animation>> m_Animations;
    std::vector<std::unique_ptr<Functional>> m_Functionals;

    float m_X, m_Y;
    int m_Width, m_Height;
};

#endif // ACTOR_H

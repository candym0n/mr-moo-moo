#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <utility>
#include <vector>

#include <functional/Functional.h>
#include <tinyxml2.h>

class Scene
{
public:
    using ExecuteFunctional = std::pair<tinyxml2::XMLElement*, std::shared_ptr<Functional>>;
    using ParallelBlock = std::vector<ExecuteFunctional>;

    Scene(std::string id);

    void AddActor(const std::string& id, std::shared_ptr<Actor> actor, int startX, int startY);

    void AddBlock(ParallelBlock block);

    bool Ended() const { return m_CurrentBlock == ParallelBlocks.end(); }

    inline std::string GetId() const { return m_Id; }
    std::vector<std::shared_ptr<Actor>> const GetActorsInvolved();

    void Update(double dt);
    void UpdateCamera(std::shared_ptr<Camera> camera);

    void Draw(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Camera> camera);

    void Begin();

private:
    std::string m_Id;
    std::map<std::string, std::shared_ptr<Actor>> m_ActorsInvolved;

    // Where actors should start out at the start of the scene
    std::map<std::string, int> m_ActorsStartingX;
    std::map<std::string, int> m_ActorsStartingY;

    // Actor ID of who the camera should follow
    std::string m_CameraFollowId;

    // All the blocks in the scene
    std::vector<ParallelBlock> ParallelBlocks;
    std::vector<ParallelBlock>::iterator m_CurrentBlock;

    // Has the current block ended?
    bool BlockEnded() const;

    // Goto the next block
    void NextBlock();
};

#endif // SCENE_H

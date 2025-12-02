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

    Scene() = default;

    void AddActor(const std::string& id, std::shared_ptr<Actor> actor);
    void SetFollowID(const std::string& id);

    void AddBlock(ParallelBlock block);

    bool Ended() const { return BlockEnded() && m_CurrentBlock == ParallelBlocks.end() - 1; }

    std::vector<std::shared_ptr<Actor>> const GetActorsInvolved();

    void Update(double dt);
    void UpdateCamera(std::shared_ptr<Camera> camera);

    void Draw(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Camera> camera);

    void Begin();

private:
    std::map<std::string, std::shared_ptr<Actor>> m_ActorsInvolved;

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

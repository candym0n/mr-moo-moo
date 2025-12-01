#include <Scene.h>

Scene::Scene(std::string id) : 
    m_Id(std::move(id))
{
}

void Scene::AddBlock(ParallelBlock block)
{
    ParallelBlocks.push_back(std::move(block));
}

void Scene::AddActor(const std::string& id, std::shared_ptr<Actor> actor, int startX, int startY)
{
    m_ActorsInvolved[id] = actor;
    
    if (startX != INT32_MIN)
        m_ActorsStartingX[id] = startX;
    
    if (startY != INT32_MIN)
        m_ActorsStartingY[id] = startY;
}

bool Scene::BlockEnded() const
{
    for (const auto& executeFunctional : *m_CurrentBlock)
    {
        std::shared_ptr<Functional> functional = executeFunctional.second;

        if (functional->IsPlaying())
            return false;
    }
    return true;
}

void Scene::NextBlock()
{
    if (Ended())
        return;

    ++m_CurrentBlock;

    for (const auto& executeFunctional : *m_CurrentBlock)
    {
        
        std::shared_ptr<Functional> functional = executeFunctional.second;
        
        tinyxml2::XMLElement* elem = executeFunctional.first;
        
        functional->Begin(elem);
    }
}

void Scene::Update(double dt)
{
    auto thing = m_ActorsInvolved.begin();

    bool allEnded = true;

    for (const auto& executeFunctional : *m_CurrentBlock)
    {
        std::shared_ptr<Functional> functional = executeFunctional.second;

        allEnded &= !functional->IsPlaying();
    }

    if (allEnded)
        NextBlock();
    
    
}

void Scene::UpdateCamera(std::shared_ptr<Camera> camera)
{
    if (m_CameraFollowId.empty())
        return;

    auto it = m_ActorsInvolved.find(m_CameraFollowId);
    if (it != m_ActorsInvolved.end())
    {
        auto actor = it->second;

        if (actor->GetX() + actor->GetWidth() / 2.0f > camera->getX() + 400.0f)
        {
            camera->setX(actor->GetX() + actor->GetWidth() / 2.0f - 400.0f);
        }
        else if (actor->GetX() + actor->GetWidth() / 2.0f < camera->getX() + 200.0f)
        {
            camera->setX(actor->GetX() + actor->GetWidth() / 2.0f - 200.0f);
        }
    }
}

void Scene::Draw(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Camera> camera)
{
    for (const auto& pair : m_ActorsInvolved) {
        auto actor = pair.second;
        actor->Draw(renderer, camera);
    }
}

void Scene::Begin()
{
    m_CurrentBlock = ParallelBlocks.begin();

    for (const auto& executeFunctional : *m_CurrentBlock)
    {
        std::shared_ptr<Functional> functional = executeFunctional.second;
        tinyxml2::XMLElement* elem = executeFunctional.first;

        functional->Begin(elem);
    }
}

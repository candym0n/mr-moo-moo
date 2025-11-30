#include <ScenePlayer.h>

ScenePlayer::ScenePlayer()
{
    m_Background = std::make_unique<Background>();
    m_Camera = std::make_shared<Camera>(0);
}

void ScenePlayer::SetBackgroundTexture(std::shared_ptr<SDL_Texture> bg)
{
    m_Background->SetTexture(bg);
}

void ScenePlayer::SetScene(std::string id)
{
    auto it = m_Scenes.find(id);
    if (it == m_Scenes.end())
        return;

    auto scene = it->second;
    
    m_Scene = scene;
}

void ScenePlayer::SetScenes(std::map<std::string, std::shared_ptr<Scene>> scenes)
{
    m_Scenes = scenes;
    SetScene("idle");
    m_Scene->Begin();
}

void ScenePlayer::Draw(std::shared_ptr<SDL_Renderer> renderer)
{
    m_Background->Draw(renderer, m_Camera);
    m_Scene->Draw(renderer, m_Camera);
}

void ScenePlayer::Update(double deltaTime)
{
    m_Scene->Update(deltaTime);
    m_Scene->UpdateCamera(m_Camera);

    if (m_Scene->Ended())
    {
        // Loop the scene
        m_Scene->Begin();
    }
}

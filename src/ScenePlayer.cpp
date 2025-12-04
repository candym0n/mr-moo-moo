#include <ScenePlayer.h>
#include <iostream>

ScenePlayer::ScenePlayer() :
    m_IdleScene(0)
{
    m_Background = std::make_unique<Background>();
    m_Camera = std::make_shared<Camera>(0);
}

void ScenePlayer::SetBackgroundTexture(std::shared_ptr<SDL_Texture> bg)
{
    m_Background->SetTexture(bg);
}

void ScenePlayer::SetScenes(std::vector<std::shared_ptr<Scene>> scenes, std::vector<int> weights, std::vector<char> shortcuts, int idleScene)
{
    m_SceneWeights = weights;
    m_TotalWeight = std::accumulate(weights.begin(), weights.end(), 0);

    m_Shortcuts = shortcuts;

    m_Scenes = scenes;
    m_IdleScene = idleScene;
    m_Scene = m_Scenes[idleScene];
    m_Scene->Begin();
}

void ScenePlayer::Draw(std::shared_ptr<SDL_Renderer> renderer)
{
    m_Background->Draw(renderer, m_Camera);
    m_Scene->Draw(renderer, m_Camera);
}

void ScenePlayer::Update(double deltaTime)
{
    if (m_Scene->Ended())
    {
        if (m_Scene != m_Scenes[m_IdleScene]) {// We just finished a special scene
            m_Scene = m_Scenes[m_IdleScene];
            m_Scene->Begin();
        }
        else if (rand() < RAND_MAX / 8) // We just finished an idle scene, and some chance we continue idle
            m_Scene->Begin();
        else {
            m_Scene = m_Scenes[GetRandomSceneIndex()];
            m_Scene->Begin();
        }
    } else {
        m_Scene->Update(deltaTime);
        m_Scene->UpdateCamera(m_Camera);
    }
}

void ScenePlayer::SetQueueScene(int sceneIndex)
{
    m_QueueScene = sceneIndex;
}

int ScenePlayer::GetSceneFromShortcut(char shortcut) const
{
    auto it = std::find(m_Shortcuts.begin(), m_Shortcuts.end(), shortcut);
    if (it != m_Shortcuts.end()) {
        int index = std::distance(m_Shortcuts.begin(), it);
        if (index >= 0 && index < m_Scenes.size())
            return index;
    }
    return -1; // Not found
}

int ScenePlayer::GetRandomSceneIndex() const
{
    // Uh oh
    if (!m_TotalWeight)
        return m_IdleScene;
    
    // We have a pre-selected scene
    if (m_QueueScene >= 0 && m_QueueScene < m_Scenes.size()) {
        int queuedScene = m_QueueScene;
        m_QueueScene = -1;
        return queuedScene;
    }

    // Random number in [0, total - 1]
    int r = rand() % m_TotalWeight;

    // Find the index
    int cumlative = 0;
    for (int i = 0; i < m_Scenes.size(); ++i) {
        if (m_SceneWeights[i] <= 0) continue;
        cumlative += m_SceneWeights[i];
        if (r < cumlative)
            return i;
    }

    return m_IdleScene; // Fallback
}

#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <string>

#include <SDL3/SDL.h>
#include <tinyxml2.h>

#include <Actor.h>
#include <HelperFunctions.h>
#include <Scene.h>

// Config class parses an XML configuration and provides access to resources.
class Config
{
public:
    // Construct Config from XML file path.
    Config(const std::string& xmlPath, std::shared_ptr<SDL_Renderer> renderer);

    // Noncopyable, but movable for resource safety.
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    ~Config() = default;

    std::shared_ptr<SDL_Texture> GetBackgroundTexture() const;

    std::vector<std::shared_ptr<Scene>> GetScenes() const;
    int GetIdleSceneIndex() const;
    std::vector<int> GetSceneWeights() const;
    std::vector<char> GetSceneShortcuts() const;

private:
    std::shared_ptr<SDL_Texture> m_BackgroundTexture;

    std::map<std::string, std::shared_ptr<Actor>> m_Actors;
    
    // XML parsing helper routines.
    void LoadFromXML(const std::string& xmlPath, std::shared_ptr<SDL_Renderer> renderer);
    void LoadActorConfig(tinyxml2::XMLElement* actorElem, std::shared_ptr<SDL_Renderer> renderer);
    void LoadSceneConfig(tinyxml2::XMLElement* sceneElem);

    tinyxml2::XMLDocument m_Doc;

    // Scene information
    std::vector<std::shared_ptr<Scene>> m_Scenes;
    std::vector<int> m_SceneWeights;
    std::vector<char> m_Shortcuts;
    int m_IdleScene = 0;
};

#endif // CONFIG_H

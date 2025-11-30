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

    // Destructor cleans up texture.
    ~Config() = default;

    // Get SDL_Texture for background.
    std::shared_ptr<SDL_Texture> getBackgroundTexture() const;

    // Get all scenes defined in the config
    std::map<std::string, std::shared_ptr<Scene>> getScenes() const;

private:
    std::shared_ptr<SDL_Texture> m_BackgroundTexture;

    std::map<std::string, std::shared_ptr<Actor>> m_Actors;
    std::map<std::string, std::shared_ptr<Scene>> m_Scenes;

    // XML parsing helper routines.
    void loadFromXML(const std::string& xmlPath, std::shared_ptr<SDL_Renderer> renderer);
    void loadActorConfig(tinyxml2::XMLElement* actorElem, std::shared_ptr<SDL_Renderer> renderer);
    void loadSceneConfig(tinyxml2::XMLElement* sceneElem);
};

#endif // CONFIG_H

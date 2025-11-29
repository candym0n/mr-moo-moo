#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include <SDL3/SDL.h>
#include <tinyxml2.h>

#include <HelperFunctions.h>

/// Config class parses an XML configuration and provides access to resources.
class Config
{
public:
    /// Construct Config from XML file path.
    Config(const std::string& xmlPath, std::shared_ptr<SDL_Renderer> renderer);

    /// Noncopyable, but movable for resource safety.
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    /// Destructor cleans up texture.
    ~Config();

    /// Get SDL_Texture for background.
    std::shared_ptr<SDL_Texture> getBackgroundTexture() const;

private:
    std::shared_ptr<SDL_Texture> m_BackgroundTexture;

    /// XML parsing helper routines.
    void loadFromXML(const std::string& xmlPath, std::shared_ptr<SDL_Renderer> renderer);
};

#endif // CONFIG_H

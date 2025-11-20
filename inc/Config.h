#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>

#include <SDL3/SDL.h>
#include <tinyxml2.h>

#include <AssetHelper.h>

/// Config class parses an XML configuration and provides access to resources.
class Config
{
public:
    /// Construct Config from XML file path.
    Config(const std::string& xmlPath, SDL_Renderer* renderer);

    /// Noncopyable, but movable for resource safety.
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    Config(Config&&) noexcept;
    Config& operator=(Config&&) noexcept;

    /// Destructor cleans up texture.
    ~Config();

    /// Get SDL_Texture for background.
    SDL_Texture* getBackgroundTexture() const;

private:
    SDL_Texture* m_BackgroundTexture;

    /// XML parsing helper routines.
    void loadFromXML(const std::string& xmlPath, SDL_Renderer* renderer);
};

#endif // __CONFIG_H__

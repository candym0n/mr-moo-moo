#include <Config.h>

Config::Config(const std::string &xmlPath, std::shared_ptr<SDL_Renderer> renderer) :
    m_BackgroundTexture(nullptr)
{
    loadFromXML(xmlPath, renderer);
}

Config::~Config()
{
    // SDL3 will destroy textures for us. Thank you, SDL.
}

std::shared_ptr<SDL_Texture> Config::getBackgroundTexture() const
{
    return m_BackgroundTexture;
}

void Config::loadFromXML(const std::string& xmlPath, std::shared_ptr<SDL_Renderer> renderer)
{
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(xmlPath.c_str()) != tinyxml2::XML_SUCCESS)
        return;

    tinyxml2::XMLElement* root = doc.FirstChildElement("ScreenSaver");
    if (!root)
        return;

    tinyxml2::XMLElement* bgElem = root->FirstChildElement("Background");
    if (!bgElem)
        return;

    const char* src = bgElem->Attribute("src");
    if (src)
    {
        m_BackgroundTexture = AssetHelper::LoadTexture(renderer, src);
    }
}

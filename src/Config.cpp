#include <Config.h>

Config::Config(const std::string &xmlPath, std::shared_ptr<SDL_Renderer> renderer) :
    m_BackgroundTexture(nullptr)
{
    loadFromXML(xmlPath, renderer);
}

std::shared_ptr<SDL_Texture> Config::getBackgroundTexture() const
{
    return m_BackgroundTexture;
}

std::map<std::string, std::shared_ptr<Scene>> Config::getScenes() const
{
    return m_Scenes;
}

void Config::loadFromXML(const std::string& xmlPath, std::shared_ptr<SDL_Renderer> renderer)
{
    std::cout << "Loading configuration from: " << xmlPath.c_str() << '\n';
    if (m_Doc.LoadFile(xmlPath.c_str()) != tinyxml2::XML_SUCCESS)
    {
        std::cout << "Failed to load XML file: " << xmlPath << '\n';
        return;
    }

    tinyxml2::XMLElement* root = m_Doc.FirstChildElement("ScreenSaver");
    if (!root) {
        std::cout << "No <ScreenSaver> root element found in XML.\n";
        return;
    }

    tinyxml2::XMLElement* bgElem = root->FirstChildElement("Background");
    if (!bgElem) {
        std::cout << "No <Background> element found in XML.\n";
        return;
    }

    const char* src = bgElem->Attribute("src");
    if (src)
        m_BackgroundTexture = HelperFunctions::LoadTexture(renderer, src);
    
    tinyxml2::XMLElement* actorsElem = root->FirstChildElement("Actors");
    if (!actorsElem) {
        std::cout << "No <Actors> element found in XML.\n";
        return;
    }

    for (tinyxml2::XMLElement* actorElem = actorsElem->FirstChildElement("Actor"); actorElem != nullptr; actorElem = actorElem->NextSiblingElement("Actor"))
        loadActorConfig(actorElem, renderer);

    tinyxml2::XMLElement* scenesElem = root->FirstChildElement("Scenes");
    if (!scenesElem) {
        std::cout << "No <Scenes> element found in XML.\n";
        return;
    }
    
    for (tinyxml2::XMLElement* sceneElem = scenesElem->FirstChildElement("Scene"); sceneElem != nullptr; sceneElem = sceneElem->NextSiblingElement("Scene"))
        loadSceneConfig(sceneElem);
}

void Config::loadSceneConfig(tinyxml2::XMLElement *sceneElem)
{
    if (!sceneElem)
        return;

    // Get basic scene metadata
    const char* sceneId = sceneElem->Attribute("id");
    const char* followId = sceneElem->Attribute("follow");
    if (!sceneId)
        return;

    // A blank slate to put configuration stuff onto
    auto scene = std::make_shared<Scene>(sceneId);

    if (followId)
        scene->SetFollowID(followId);

    // Load actors involved in the scene
    for (tinyxml2::XMLElement* actorElem = sceneElem->FirstChildElement("Actor"); actorElem != nullptr; actorElem = actorElem->NextSiblingElement("Actor"))
    {
        const char* actorId = actorElem->Attribute("id");
        if (!actorId)
            continue;

        int startX = actorElem->IntAttribute("x", INT32_MIN);
        int startY = actorElem->IntAttribute("y", INT32_MIN);

        auto actorIt = m_Actors.find(actorId);
        if (actorIt == m_Actors.end())
            continue;

        scene->AddActor(actorId, actorIt->second, startX, startY);
    }

    // Load the plot
    tinyxml2::XMLElement* plotElem = sceneElem->FirstChildElement("Plot");
    if (!plotElem)
        return;
        
    for (tinyxml2::XMLElement* funcElem = plotElem->FirstChildElement("ExecuteFunctional"); funcElem != nullptr; funcElem = funcElem->NextSiblingElement("ExecuteFunctional"))
    {
        const char* actorId = funcElem->Attribute("actor");
        const char* typeStr = funcElem->Attribute("type");
        if (!actorId || !typeStr)
            continue;

        std::string funcType = typeStr;

        auto actorIt = m_Actors.find(actorId);
        if (actorIt == m_Actors.end())
            continue;

        std::shared_ptr<Actor> actor = actorIt->second;

        auto functional = actor->GetFunctional(funcType);
        if (!functional)
            continue;

        scene->AddBlock({ { funcElem, functional } });
    }

    m_Scenes[sceneId] = scene;
}

void Config::loadActorConfig(tinyxml2::XMLElement *actorElem, std::shared_ptr<SDL_Renderer> renderer)
{
    if (!actorElem)
        return;
    
    // Get actor ID
    const char* actorId = actorElem->Attribute("id");

    // Get width and height of actor
    float actorWidth = actorElem->FloatAttribute("width", 64.0f);
    float actorHeight = actorElem->FloatAttribute("height", 64.0f);

    // A blank slate to put configuration stuff onto
    auto actor = std::make_shared<Actor>(actorId, actorWidth, actorHeight);

    // Load animations for the actor
    for (tinyxml2::XMLElement* animElem = actorElem->FirstChildElement("Animation"); animElem != nullptr; animElem = animElem->NextSiblingElement("Animation"))
    {
        const char* idStr = animElem->Attribute("id");
        const char* sheetStr = animElem->Attribute("sheet");
        const char* framesStr = animElem->Attribute("frames");
        
        float frameDur = animElem->FloatAttribute("duration") / 1000;

        if (!idStr || !sheetStr)
            continue;

        std::string animationId = idStr;
        std::string animationSheet = sheetStr;
        std::stringstream framesSS = std::stringstream(framesStr ? framesStr : "0-0");

        auto texture = HelperFunctions::LoadTexture(renderer, animationSheet);
        if (texture)
        {
            int startFrame, endFrame;
            char dash;
            framesSS >> startFrame >> dash >> endFrame;
            actor->IncludeAnimation(animationId, texture, actorWidth, actorHeight, frameDur, startFrame, endFrame);
        } else
            throw std::runtime_error("Failed to load spritesheet: " + animationSheet + " when loading animation " + animationId + " for actor " + std::string(actorId));
    }

    // Load functionals defined for the actor
    for (tinyxml2::XMLElement* funcElem = actorElem->FirstChildElement("Functional"); funcElem != nullptr; funcElem = funcElem->NextSiblingElement("Functional"))
    {
        const char* typeStr = funcElem->Attribute("type");
        if (!typeStr)
            continue;

        std::string funcType = typeStr;

        actor->RegisterFunctional(funcType, funcElem);
    }

    // Store the actor in the config's actor map
    m_Actors[actorId] = actor;
}

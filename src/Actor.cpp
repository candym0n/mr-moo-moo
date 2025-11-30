#include <Actor.h>

Actor::Actor(std::string id, int width, int height) :
    m_Id(std::move(id)),
    m_Width(width),
    m_Height(height)
{
}

void Actor::RegisterFunctional(std::string& type, tinyxml2::XMLElement* elem)
{
    auto functional = FunctionalFactory::Instance().Create(type, *this, elem);
    if (functional)
       m_Functionals[type] = std::move(functional);
}

void Actor::IncludeAnimation(std::string& id, std::shared_ptr<SDL_Texture> sheet, float frameWidth, float frameHeight, float frameDuration, int start, int end)
{
    auto animation = std::make_shared<Animation>();
    animation->SetTexture(sheet, frameWidth, frameHeight, frameDuration, start, end);
    m_Animations[id] = animation;
}

void Actor::SetCurrentAnimation(std::string& id)
{
    auto it = m_Animations.find(id);
    if (it != m_Animations.end())
        m_CurrentAnimation = it->second;
}

std::shared_ptr<Functional> Actor::GetFunctional(std::string &type)
{
    auto it = m_Functionals.find(type);
    if (it != m_Functionals.end())
        return it->second;
    return nullptr;
}

void Actor::Update(double deltaTime)
{
    for (auto& pair : m_Functionals)
    {
        auto& functional = pair.second;
        functional->Update(deltaTime);
    }

    if (m_CurrentAnimation)
    {
        m_CurrentAnimation->Update(deltaTime);
    }
}

void Actor::Draw(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<Camera> camera)
{
    if (m_CurrentAnimation)
    {
        m_CurrentAnimation->Draw(renderer, camera, static_cast<int>(m_X), static_cast<int>(m_Y), m_Width, m_Height);
    }
}

void Actor::SetPosition(float x, float y)
{
    m_X = x;
    m_Y = y;
}

void Actor::MoveBy(float dx, float dy)
{
    m_X += dx;
    m_Y += dy;
}

std::string Actor::GetId()
{
    return m_Id;
}

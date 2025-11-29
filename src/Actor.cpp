#include <Actor.h>

Actor::Actor(std::string id, int width, int height) :
    m_Id(std::move(id)),
    m_Width(width),
    m_Height(height)
{
}

void Actor::RegisterFunctional(std::string& type, FunctionalCreationArgs arguments)
{
    auto functional = FunctionalFactory::Instance().Create(type, *this, arguments);
    if (functional)
       m_Functionals.push_back(std::move(functional));
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

void Actor::Update(double deltaTime)
{
    for (auto& functional : m_Functionals)
    {
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

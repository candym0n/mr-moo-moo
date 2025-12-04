#include <functional/FunctionalFloat.h>
#include <cmath>

FunctionalFloat::FunctionalFloat(Actor &actor, tinyxml2::XMLElement* elem) : Functional(actor)
{
    m_Float = elem->Attribute("animation");
}

void FunctionalFloat::Update(double dt)
{
    if (!IsPlaying())
        return;

    float currentX = m_Actor.GetX();
    float currentY = m_Actor.GetY();

    float directionX = m_DestinationX - currentX;
    float directionY = m_DestinationY - currentY;
    float distance = std::sqrt(directionX * directionX + directionY * directionY);

    if (distance < 1.0f) {
        m_Actor.SetPosition(m_DestinationX, m_DestinationY);
        Stop();
        return;
    }

    float moveX = (directionX / distance) * m_Speed * static_cast<float>(dt);
    float moveY = (directionY / distance) * m_Speed * static_cast<float>(dt);

    if (std::abs(moveX) > std::abs(directionX))
        moveX = directionX;
    if (std::abs(moveY) > std::abs(directionY))
        moveY = directionY;

    m_Actor.MoveBy(moveX, moveY);
}

void FunctionalFloat::Begin(tinyxml2::XMLElement *elem)
{
    Functional::Begin(elem);

    // Parse arguments
    m_Speed = elem->FloatAttribute("speed", 50.0f);
    const char* floatAnimStr = elem->Attribute("animation"); // Can overwrite default animation

    const char* destinationXStr = elem->Attribute("destinationX");
    const char* destiniationYStr = elem->Attribute("destinationY");

    m_DestinationX = destinationXStr ? HelperFunctions::ParseNumberOrRandom(destinationXStr) : m_Actor.GetX();
    m_DestinationY = destiniationYStr ? HelperFunctions::ParseNumberOrRandom(destiniationYStr) : m_Actor.GetY();

    std::string floatAnim = floatAnimStr ? floatAnimStr : m_Float;

    m_Actor.SetCurrentAnimation(floatAnim, true, true);
}

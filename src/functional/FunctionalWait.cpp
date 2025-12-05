#include <functional/FunctionalWait.h>

void FunctionalWait::Begin(tinyxml2::XMLElement *elem)
{
    Functional::Begin(elem);

    m_TimeLeft = elem->FloatAttribute("duration") / 1000;
}

void FunctionalWait::Update(double dt)
{
    m_TimeLeft -= dt;

    if (m_TimeLeft <= 0)
        Stop();
}

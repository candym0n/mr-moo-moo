#include <functional/FunctionalTeleport.h>
#include <iostream>

void FunctionalTeleport::Begin(tinyxml2::XMLElement* elem)
{
    Functional::Begin(elem); // Unnecessary but best practice
    
    float x = elem->FloatAttribute("x", m_Actor.GetX());
    float y = elem->FloatAttribute("y", m_Actor.GetY());

    m_Actor.SetPosition(x, y);

    Stop();
}

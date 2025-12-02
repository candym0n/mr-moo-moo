#include <functional/FunctionalAnimate.h>

void FunctionalAnimate::Begin(tinyxml2::XMLElement *elem)
{
    Functional::Begin(elem);

    const char* animationStr = elem->Attribute("animation");

    if (!animationStr)
        Stop();
    else {
        m_Animation = animationStr;
        m_Actor.SetCurrentAnimation(m_Animation, true, false);
        m_Actor.PlayAnimation();
    }
}

void FunctionalAnimate::Update(double dt)
{
    if (!m_Actor.IsPlaying())
        Stop();
}

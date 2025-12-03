#include <functional/FunctionalAnimate.h>

void FunctionalAnimate::Begin(tinyxml2::XMLElement *elem)
{
    Functional::Begin(elem);

    const char* animationStr = elem->Attribute("animation");
    bool shouldLoop = elem->BoolAttribute("loop", false);
    m_Duration = shouldLoop ? elem->FloatAttribute("duration", -1.0f) : -1.0f;

    if (!animationStr)
        Stop();
    else {
        m_Animation = animationStr;
        m_Actor.SetCurrentAnimation(m_Animation, true, shouldLoop);
        m_Actor.PlayAnimation();
    }

    m_Elapsed = 0.0f;
}

void FunctionalAnimate::Update(double dt)
{
    if (!IsPlaying())
        return;

    m_Elapsed += static_cast<float>(dt);

    if (m_Duration > 0.0f && m_Elapsed >= m_Duration) {
        Stop();
        return;
    }

    if (!m_Actor.IsPlaying())
        Stop();
}

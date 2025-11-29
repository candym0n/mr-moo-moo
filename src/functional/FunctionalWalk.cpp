#include <functional/FunctionalWalk.h>

FunctionalWalk::FunctionalWalk(Actor& actor, FunctionalCreationArgs& arguments) : Functional(actor)
{
    // Ignore my use of raw pointers here....
    auto* args = dynamic_cast<FunctionalWalkCreationArgs*>(&arguments);
    if (!args)
        return;
    
    m_WalkLeft = std::move(args->left);
    m_WalkRight =  std::move(args->right);
    m_Idle = std::move(args->idle);

    SetPhase(WalkingPhase::StandingStill);
}

void FunctionalWalk::Update(double deltaTime) 
{
    m_PhaseElapsedTime += deltaTime;

    if (m_PhaseElapsedTime < 0.5)
        return; // Small delay before starting movement

    switch (m_CurrentPhase)
    {
        case WalkingPhase::WalkingRight:
        {
            // Move actor to the right
            m_Actor.MoveBy(m_Speed * static_cast<float>(deltaTime), 0.0f);
            if (m_Actor.GetX() >= m_DestinationX)
            {
                SetPhase(WalkingPhase::StandingStill);
                Stop();
            }
            break;
        }
        case WalkingPhase::WalkingLeft:
        {
            // Move actor to the left
            m_Actor.MoveBy(-m_Speed * static_cast<float>(deltaTime), 0.0f);
            if (m_Actor.GetX() <= m_DestinationX)
            {
                SetPhase(WalkingPhase::StandingStill);
                Stop();
            }
            break;
        }
        case WalkingPhase::StandingStill:
        {
            // Determine walking direction
            if (m_DestinationX > m_Actor.GetX())
            {
                SetPhase(WalkingPhase::WalkingRight);
            } else if (m_DestinationX < m_Actor.GetX()) {
                SetPhase(WalkingPhase::WalkingLeft);
            } else {
                // Already at destination
                Stop();
            }
            
            break;
        }
    }
}

void FunctionalWalk::SetPhase(WalkingPhase phase)
{
    m_CurrentPhase = phase;

    switch (m_CurrentPhase)
    {
        case WalkingPhase::WalkingRight:
            m_Actor.SetCurrentAnimation(m_WalkRight);
            break;
        case WalkingPhase::WalkingLeft:
            m_Actor.SetCurrentAnimation(m_WalkLeft);
            break;
        case WalkingPhase::StandingStill:
            m_PhaseElapsedTime = 0.0;
            m_Actor.SetCurrentAnimation(m_Idle);
            break;
    }
}

void FunctionalWalk::Begin(tinyxml2::XMLElement *elem)
{
    // Parse arguments
    m_Speed = elem->FloatAttribute("speed", 50.0f);

    const char* destinationBuffer = nullptr;
    elem->QueryStringAttribute("destinationX", &destinationBuffer);
    m_DestinationX = HelperFunctions::ParseNumberOrRandom(destinationBuffer ? destinationBuffer : "random -400 400");

    // We start at a stand
    SetPhase(WalkingPhase::StandingStill);
}

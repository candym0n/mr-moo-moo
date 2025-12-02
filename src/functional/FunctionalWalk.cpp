#include <functional/FunctionalWalk.h>
#include <iostream>

FunctionalWalk::FunctionalWalk(Actor& actor, tinyxml2::XMLElement* elem) : Functional(actor)
{   
    m_WalkLeft = elem->Attribute("left");
    m_WalkRight = elem->Attribute("right");
    m_Idle = elem->Attribute("idle");
    m_LeftToStand = elem->Attribute("left_to_stand");
    m_StandToLeft = elem->Attribute("stand_to_left");
    m_RightToStand = elem->Attribute("right_to_stand");
    m_StandToRight = elem->Attribute("stand_to_right");

    SetPhase(WalkingPhase::StandingStill);
}

void FunctionalWalk::Update(double deltaTime) 
{
    if (!IsPlaying())
        return;

    switch (m_CurrentPhase) {
        case WalkingPhase::StandingStill:
            if (m_Actor.GetX() > m_DestinationX)
                SetPhase(WalkingPhase::TurningSTL);
            else if (m_Actor.GetX() < m_DestinationX)
                SetPhase(WalkingPhase::TurningSTR);
            else
                Stop(); // We are already there! (EXTREME EDGE CASE)
            break;
        case WalkingPhase::TurningSTL:
            if (!m_Actor.IsPlaying())
                SetPhase(WalkingPhase::WalkingLeft);
            break;
        case WalkingPhase::TurningSTR:
            if (!m_Actor.IsPlaying())
                SetPhase(WalkingPhase::WalkingRight);
            break;
        case WalkingPhase::WalkingLeft:
            if (m_Actor.GetX() <= m_DestinationX)
                SetPhase(WalkingPhase::TurningLTS);
            else
                m_Actor.MoveBy(-m_Speed * deltaTime, 0);
            break;
        case WalkingPhase::WalkingRight:
            if (m_Actor.GetX() >= m_DestinationX)
                SetPhase(WalkingPhase::TurningRTS);
            else
                m_Actor.MoveBy(m_Speed * deltaTime, 0);
            break;
        case WalkingPhase::TurningLTS:
        case WalkingPhase::TurningRTS:
            if (!m_Actor.IsPlaying()) {
                SetPhase(WalkingPhase::StandingStill);
                Stop();
            }
            break;
    }
}

void FunctionalWalk::SetPhase(WalkingPhase phase)
{
    m_CurrentPhase = phase;

    switch (m_CurrentPhase)
    {
        case WalkingPhase::WalkingRight:
            m_Actor.SetCurrentAnimation(m_WalkRight, true, true);
            break;
        case WalkingPhase::WalkingLeft:
            m_Actor.SetCurrentAnimation(m_WalkLeft, true, true);
            break;
        case WalkingPhase::StandingStill:
            m_Actor.SetCurrentAnimation(m_Idle, true, false);
            break;
        case WalkingPhase::TurningLTS:
            m_Actor.SetCurrentAnimation(m_LeftToStand, true, false);
            break;
        case WalkingPhase::TurningRTS:
            m_Actor.SetCurrentAnimation(m_RightToStand, true, false);
            break;
        case WalkingPhase::TurningSTL:
            m_Actor.SetCurrentAnimation(m_StandToLeft, true, false);
            break;
        case WalkingPhase::TurningSTR:
            m_Actor.SetCurrentAnimation(m_StandToRight, true, false);
            break;
    }
}

void FunctionalWalk::Begin(tinyxml2::XMLElement* elem)
{
    Functional::Begin(elem);

    // Parse arguments
    m_Speed = elem->FloatAttribute("speed", 50.0f);

    const char* destinationStr = elem->Attribute("destinationX");
    m_DestinationX = HelperFunctions::ParseNumberOrRandom(destinationStr ? destinationStr : "random -400 400");

    SetPhase(WalkingPhase::StandingStill);
}

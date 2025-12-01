#ifndef FUNCTIONAL_WALK_H
#define FUNCTIONAL_WALK_H

#include <tinyxml2.h>

#include "Functional.h"
#include "FunctionalFactory.h"
#include <Animation.h>
#include <HelperFunctions.h>

class FunctionalWalk : public Functional {
public:
    FunctionalWalk(Actor& actor, tinyxml2::XMLElement* elem);

    void Begin(tinyxml2::XMLElement* elem) override; // Called at the start of each duration
    void Update(double deltaTime) override;          // Called every frame in a duration

private:
    // Animation IDs
    std::string m_WalkRight;
    std::string m_WalkLeft;
    std::string m_Idle;
    std::string m_LeftToStand;
    std::string m_RightToStand;
    std::string m_StandToLeft;
    std::string m_StandToRight;

    // Destination coordinate and speed
    float m_DestinationX;
    float m_Speed;

    // Current walking phase
    enum class WalkingPhase {
        WalkingRight,
        WalkingLeft,
        StandingStill,
        TurningLTS,
        TurningSTL,
        TurningRTS,
        TurningSTR
    } m_CurrentPhase;

    // Transitioning between phases
    void SetPhase(WalkingPhase phase);
};

REGISTER_FUNCTIONAL("walk", FunctionalWalk);

#endif // FUNTIONAL_WALK_H

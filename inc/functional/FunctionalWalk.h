#ifndef FUNCTIONAL_WALK_H
#define FUNCTIONAL_WALK_H

#include <tinyxml2.h>

#include "Functional.h"
#include "FunctionalFactory.h"
#include <Animation.h>
#include <HelperFunctions.h>

struct FunctionalWalkCreationArgs : public FunctionalCreationArgs {
    // Animation IDs
    std::string right; // Walk to the right
    std::string left;  // Walk to the left
    std::string idle;  // Stand still, facing away from the camera
};

struct FunctionalWalkRuntimeArgs : public FunctionalRuntimeArgs {
    float destinationX; // X coordinate to walk to
    float speed;        // Speed of movement
};

class FunctionalWalk : public Functional {
public:
    FunctionalWalk(Actor& actor, FunctionalCreationArgs& arguments);

    void Begin(tinyxml2::XMLElement* elem) override; // Called at the start of each duration
    void Update(double deltaTime) override;          // Called every frame in a duration

private:
    // Animation IDs
    std::string m_WalkRight;
    std::string m_WalkLeft;
    std::string m_Idle;

    // Destination coordinate and speed
    float m_DestinationX;
    float m_Speed;

    // Current walking phase
    enum class WalkingPhase {
        WalkingRight,
        WalkingLeft,
        StandingStill
    } m_CurrentPhase;

    // Transitioning between phases
    void SetPhase(WalkingPhase phase);

    // How long have we been in the current phase?
    double m_PhaseElapsedTime = 0.0;
};

REGISTER_FUNCTIONAL("walk", FunctionalWalk, FunctionalWalkCreationArgs);

#endif // FUNTIONAL_WALK_H

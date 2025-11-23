#ifndef FUNCTIONAL_WALK_H
#define FUNCTIONAL_WALK_H

#include "Functional.h"
#include "FunctionalFactory.h"
#include <Animation.h>

struct FunctionalWalkCreationArgs : public Functional::CreationArgs {
    std::unique_ptr<Animation> right; // Walk to th right
    std::unique_ptr<Animation> left;  // Walk to the left
    std::unique_ptr<Animation> idle;  // Stand still, facing away from the camera
};

struct FunctionalWalkRuntimeArgs : public Functional::RuntimeArgs {

};

class FunctionalWalk : public Functional {
    FunctionalWalk(CreationArgs& arguments);

    void Perform(Actor& actor, RuntimeArgs& arguments) override;
};

REGISTER_FUNCTIONAL("walk", FunctionalWalk, FunctionalWalkCreationArgs);

#endif // FUNTIONAL_WALK_H

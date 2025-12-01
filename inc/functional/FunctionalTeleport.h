#ifndef FUNCTIONAL_TELEPORT_H
#define FUNCTIONAL_TELEPORT_H

#include <tinyxml2.h>

#include "Functional.h"
#include "FunctionalFactory.h"
#include <Animation.h>
#include <HelperFunctions.h>

class FunctionalTeleport : public Functional {
public:
    FunctionalTeleport(Actor& actor, tinyxml2::XMLElement*) : Functional(actor) {}

    void Update(double dt) override {};
    void Begin(tinyxml2::XMLElement* elem) override; // Called at the start of each duration
};

REGISTER_FUNCTIONAL("teleport", FunctionalTeleport);

#endif // FUNTIONAL_TELEPORT_H

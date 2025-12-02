#ifndef FUNCTIONAL_WAIT_H
#define FUNCTIONAL_WAIT_H

#include <tinyxml2.h>

#include "Functional.h"
#include "FunctionalFactory.h"
#include <Animation.h>
#include <HelperFunctions.h>

class FunctionalWait : public Functional {
public:
    FunctionalWait(Actor& actor, tinyxml2::XMLElement*) : Functional(actor) {}

    void Update(double dt) override;
    void Begin(tinyxml2::XMLElement* elem) override; // Called at the start of each duration
private:
    double m_TimeLeft;
};

REGISTER_FUNCTIONAL("wait", FunctionalWait);

#endif // FUNTIONAL_Wait_H

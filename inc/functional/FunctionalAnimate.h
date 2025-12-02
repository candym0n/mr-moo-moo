#ifndef FUNCTIONAL_ANIMATE_H
#define FUNCTIONAL_ANIMATE_H

#include <tinyxml2.h>

#include "Functional.h"
#include "FunctionalFactory.h"
#include <Animation.h>
#include <HelperFunctions.h>

class FunctionalAnimate : public Functional {
public:
    FunctionalAnimate(Actor& actor, tinyxml2::XMLElement*) : Functional(actor) {}

    void Update(double dt) override;
    void Begin(tinyxml2::XMLElement* elem) override; // Called at the start of each duration
private:
    std::string m_Animation; // The animation to animate
};

REGISTER_FUNCTIONAL("animate", FunctionalAnimate);

#endif // FUNTIONAL_ANIMATE_H

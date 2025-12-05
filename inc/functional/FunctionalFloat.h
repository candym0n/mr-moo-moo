#ifndef FUNCTIONAL_FLOAT_H
#define FUNCTIONAL_FLOAT_H

#include <tinyxml2.h>

#include "Functional.h"
#include "FunctionalFactory.h"
#include <Animation.h>
#include <HelperFunctions.h>

class FunctionalFloat : public Functional {
public:
    FunctionalFloat(Actor& actor, tinyxml2::XMLElement*);

    void Update(double dt) override;
    void Begin(tinyxml2::XMLElement* elem) override; // Called at the start of each duration
private:
    std::string m_Float; // The float animation

    float m_Speed;
    float m_DestinationX;
    float m_DestinationY;
};

REGISTER_FUNCTIONAL("float", FunctionalFloat);

#endif // FUNTIONAL_FLOAT_H

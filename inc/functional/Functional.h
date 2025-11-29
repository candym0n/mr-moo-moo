#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <tinyxml2.h>

#include <Actor.h>

class Actor; // Forward declartion to keep compiler happy

struct FunctionalCreationArgs {
    virtual ~FunctionalCreationArgs() {};
};

struct FunctionalRuntimeArgs {
    virtual ~FunctionalRuntimeArgs() {};
};

class Functional {
public:
    Functional(Actor& actor) : m_Actor(actor) {}

    virtual void Begin(tinyxml2::XMLElement* arguments) {};
    virtual void Update(double deltaTime) {};

    constexpr bool IsPlaying() { return m_Playing; }
protected:
    void Stop() { m_Playing = false; }
    Actor& m_Actor;
private:
    bool m_Playing = false;
};

#endif // FUNCTIONAL_H

#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <Actor.h>

class Functional {
public:
    struct CreationArgs {
        virtual ~CreationArgs() {};
    };

    struct RuntimeArgs {
        virtual ~RuntimeArgs() {};
    };

    Functional(const CreationArgs& args);

    virtual void Perform(RuntimeArgs& arguments) {};
};

#endif // FUNCTIONAL_H

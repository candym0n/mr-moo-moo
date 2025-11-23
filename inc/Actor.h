#ifndef ACTOR_H
#define ACTOR_H

#include <memory>
#include <string>
#include <vector>

#include <functional/Functional.h>
#include <functional/FunctionalFactory.h>

class Actor {
public:
    Actor(std::string id);

    void RegisterFunctional(std::string type, Functional::CreationArgs arguments);

    std::string GetId();
private:
    std::string m_Id;
    std::vector<std::unique_ptr<Functional>> m_Functionals;
};

#endif // ACTOR_H

#ifndef FUNCTIONAL_FACTORY_H
#define FUNCTIONAL_FACTORY_H

#include <functional>
#include <memory>
#include <string>
#include <map>

#include <Actor.h>
#include "Functional.h"

// Helper registration macro
#define REGISTER_FUNCTIONAL(id, Type, CreationArgsType) \
    namespace { \
        const bool registered_##Type = [] { \
            FunctionalFactory::Instance().RegisterFunctional( \
                id, \
                [](Actor& actor, FunctionalCreationArgs& args) { \
                    CreationArgsType& typedArgs = dynamic_cast<CreationArgsType&>(args); \
                    return std::make_unique<Type>(actor, typedArgs); \
                }); \
            return true; \
        }(); \
    }

class Functional;
class Actor;
struct FunctionalCreationArgs;

class FunctionalFactory {
public:
    using Creator = std::function<std::unique_ptr<Functional>(Actor& actor, FunctionalCreationArgs& args)>;

    static FunctionalFactory& Instance();

    void RegisterFunctional(const std::string& id, Creator creator);
    std::unique_ptr<Functional> Create(const std::string& id, Actor& actor, FunctionalCreationArgs& args);

private:
    std::map<std::string, Creator> creators;
};

#endif // FUNCTIONAL_FACTORY_H

#ifndef FUNCTIONAL_FACTORY_H
#define FUNCTIONAL_FACTORY_H

#include <functional>
#include <memory>
#include <string>
#include <map>

#include <Actor.h>
#include <tinyxml2.h>
#include "Functional.h"

// Helper registration macro
#define REGISTER_FUNCTIONAL(id, Type) \
    namespace { \
        const bool registered_##Type = [] { \
            FunctionalFactory::Instance().RegisterFunctional( \
                id, \
                [](Actor& actor, tinyxml2::XMLElement* elem) { \
                    return std::make_unique<Type>(actor, elem); \
                }); \
            return true; \
        }(); \
    }

class Functional;
class Actor;
struct FunctionalCreationArgs;

class FunctionalFactory {
public:
    using Creator = std::function<std::unique_ptr<Functional>(Actor& actor, tinyxml2::XMLElement* elem)>;

    static FunctionalFactory& Instance();

    void RegisterFunctional(const std::string& id, Creator creator);
    std::unique_ptr<Functional> Create(const std::string& id, Actor& actor, tinyxml2::XMLElement* elem);

private:
    std::map<std::string, Creator> creators;
};

#endif // FUNCTIONAL_FACTORY_H

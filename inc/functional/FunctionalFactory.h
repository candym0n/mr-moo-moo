#ifndef FUNCTIONAL_FACTORY_H
#define FUNCTIONAL_FACTORY_H

#include <functional>
#include <memory>
#include <string>
#include <map>

#include "Functional.h"

// Helper registration macro
#define REGISTER_FUNCTIONAL(id, Type, CreationArgsType) \
    namespace { \
        const bool registered_##Type = [] { \
            FunctionalFactory::Instance().RegisterFunctional( \
                id, \
                [](Functional::CreationArgs& args) { \
                    CreationArgsType& typedArgs = dynamic_cast<CreationArgsType&>(args); \
                    return std::make_unique<Type>(typedArgs); \
                }); \
            return true; \
        }(); \
    }

class FunctionalFactory {
public:
    using Creator = std::function<std::unique_ptr<Functional>(Functional::CreationArgs& args)>;

    static FunctionalFactory& Instance();

    void RegisterFunctional(const std::string& id, Creator creator);
    std::unique_ptr<Functional> Create(const std::string& id, Functional::CreationArgs& args);

private:
    std::map<std::string, Creator> creators;
};

#endif // FUNCTIONAL_FACTORY_H

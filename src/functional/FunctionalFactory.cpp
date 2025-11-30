#include <functional/FunctionalFactory.h>

FunctionalFactory &FunctionalFactory::Instance()
{
    static FunctionalFactory inst;
    return inst;
}


void FunctionalFactory::RegisterFunctional(const std::string& id, Creator creator) {
    creators[id] = creator;
}

std::unique_ptr<Functional> FunctionalFactory::Create(const std::string& id, Actor& actor, tinyxml2::XMLElement* elem) {
    auto it = creators.find(id);
    if (it != creators.end()) {
        return (it->second)(actor, elem);
    }
    return nullptr;
}

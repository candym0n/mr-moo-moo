#include <functional/FunctionalFactory.h>

FunctionalFactory &FunctionalFactory::Instance()
{
    static FunctionalFactory inst;
    return inst;
}


void FunctionalFactory::RegisterFunctional(const std::string& id, Creator creator) {
    creators[id] = creator;
}

std::unique_ptr<Functional> FunctionalFactory::Create(const std::string& id, Functional::CreationArgs& args) {
    auto it = creators.find(id);
    if (it != creators.end()) {
        return (it->second)(args);
    }
    return nullptr;
}

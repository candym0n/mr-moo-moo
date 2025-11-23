#include <Actor.h>

Actor::Actor(std::string id) :
    m_Id(std::move(id))
{
}

void Actor::RegisterFunctional(std::string type, Functional::CreationArgs arguments)
{
    //auto functional = FunctionalFactory::Instance().Create(type, arguments);
    //if (functional)
     //   m_Functionals.push_back(std::move(functional));
}

std::string Actor::GetId()
{
    return m_Id;
}

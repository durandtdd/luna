#include "variable.hpp"


Variable::Variable(Type type, const std::string& name):
    type(type),
    name(name)
{
}


std::string Variable::str() const
{
    return type.str() + " " + name;
}

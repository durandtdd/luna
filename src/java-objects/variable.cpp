#include "variable.hpp"


bool operator==(const Variable& var1, const Variable& var2)
{
    return (var1.type == var2.type) && (var1.name == var2.name);
}


bool operator!=(const Variable& var1, const Variable& var2)
{
    return !(var1 == var2);
}

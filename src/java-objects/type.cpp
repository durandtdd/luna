#include "type.hpp"


bool operator==(const Type& type1, const Type& type2)
{
    return (type1.type == type2.type) &&
            (type1.object == type2.object) &&
            (type1.dimensions == type2.dimensions);
}


bool operator!=(const Type& type1, const Type& type2)
{
    return !(type1 == type2);
}

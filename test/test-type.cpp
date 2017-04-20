#include "catch/catch.hpp"

#include "../src/java-objects/type.hpp"


TEST_CASE("Types")
{
    REQUIRE(Type::tBoolean().type == Type::Boolean);
    REQUIRE(Type::tByte().type == Type::Byte);
    REQUIRE(Type::tChar().type == Type::Char);
    REQUIRE(Type::tDouble().type == Type::Double);
    REQUIRE(Type::tFloat().type == Type::Float);
    REQUIRE(Type::tInt().type == Type::Int);
    REQUIRE(Type::tLong().type == Type::Long);
    REQUIRE(Type::tShort().type == Type::Short);
    REQUIRE(Type::tObject("String").type == Type::Object);
    REQUIRE(Type::tObject("String").object == "String");
    REQUIRE(Type::tObject("java.lang.String", 2).type == Type::Object);
    REQUIRE(Type::tObject("java.lang.String", 2).object == "java.lang.String");
    REQUIRE(Type::tObject("java.lang.String", 2).dimensions == 2);
}

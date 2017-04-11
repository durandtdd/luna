#include "catch/catch.hpp"

#include "../src/java-objects/type.hpp"


TEST_CASE("Types")
{
    REQUIRE(Type::tBoolean().str() == "boolean");
    REQUIRE(Type::tByte().str() == "byte");
    REQUIRE(Type::tChar().str() == "char");
    REQUIRE(Type::tDouble().str() == "double");
    REQUIRE(Type::tFloat().str() == "float");
    REQUIRE(Type::tInt().str() == "int");
    REQUIRE(Type::tLong().str() == "long");
    REQUIRE(Type::tShort().str() == "short");
    REQUIRE(Type::tObject("String").str() == "String");
    REQUIRE(Type::tObject("java.lang.String", 2).str() == "java.lang.String[][]");
}

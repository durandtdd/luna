#include "test.hpp"

#include "../src/java-objects/type.hpp"


void testType()
{
    ASSERT_EQUAL(Type(Type::Boolean, "", 0).str(), "boolean");
    ASSERT_EQUAL(Type(Type::Byte, "", 0).str(), "byte");
    ASSERT_EQUAL(Type(Type::Char, "", 0).str(), "char");
    ASSERT_EQUAL(Type(Type::Double, "", 0).str(), "double");
    ASSERT_EQUAL(Type(Type::Float, "", 0).str(), "float");
    ASSERT_EQUAL(Type(Type::Int, "", 0).str(), "int");
    ASSERT_EQUAL(Type(Type::Long, "", 0).str(), "long");
    ASSERT_EQUAL(Type(Type::Short, "", 0).str(), "short");
    ASSERT_EQUAL(Type(Type::Object, "String", 0).str(), "String");
    ASSERT_EQUAL(Type(Type::Object, "java.lang.String", 2).str(), "java.lang.String[][]");
}

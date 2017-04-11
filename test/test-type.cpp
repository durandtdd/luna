#include "test.hpp"

#include "../src/java-objects/type.hpp"


void testType()
{
    ASSERT_EQUAL(Type::tBoolean().str(), "boolean");
    ASSERT_EQUAL(Type::tByte().str(), "byte");
    ASSERT_EQUAL(Type::tChar().str(), "char");
    ASSERT_EQUAL(Type::tDouble().str(), "double");
    ASSERT_EQUAL(Type::tFloat().str(), "float");
    ASSERT_EQUAL(Type::tInt().str(), "int");
    ASSERT_EQUAL(Type::tLong().str(), "long");
    ASSERT_EQUAL(Type::tShort().str(), "short");
    ASSERT_EQUAL(Type::tObject("String").str(), "String");
    ASSERT_EQUAL(Type::tObject("java.lang.String", 2).str(), "java.lang.String[][]");
}

#include "test.hpp"

#include "../src/descriptor-parser.hpp"


bool equal(Type t, Type::Enum type, const std::string& object, uint32 dimensions)
{
    if(t.type != type)
        return false;

    if(t.object != object)
        return false;

    if(t.dimensions != dimensions)
        return false;

    return true;
}


void testDescriptorParser()
{
    std::string str = "BCDFILjava/lang/Object;SZV[B[[B";
    auto it = str.begin();

    ASSERT_TRUE(equal(parseDescriptor(it, str.end()), Type::Byte, "", 0));
    ASSERT_TRUE(equal(parseDescriptor(it, str.end()), Type::Char, "", 0));
    ASSERT_TRUE(equal(parseDescriptor(it, str.end()), Type::Double, "", 0));
    ASSERT_TRUE(equal(parseDescriptor(it, str.end()), Type::Float, "", 0));
    ASSERT_TRUE(equal(parseDescriptor(it, str.end()), Type::Int, "", 0));
    ASSERT_TRUE(equal(parseDescriptor(it, str.end()), Type::Object, "java.lang.Object", 0));
    ASSERT_TRUE(equal(parseDescriptor(it, str.end()), Type::Short, "", 0));
    ASSERT_TRUE(equal(parseDescriptor(it, str.end()), Type::Boolean, "", 0));
    ASSERT_TRUE(equal(parseDescriptor(it, str.end()), Type::Void, "", 0));
    ASSERT_TRUE(equal(parseDescriptor(it, str.end()), Type::Byte, "", 1));
    ASSERT_TRUE(equal(parseDescriptor(it, str.end()), Type::Byte, "", 2));

    str = "[[[";
    ASSERT_ERROR(parseDescriptor(str.begin(), str.end()));

    str = "[[[T";
    ASSERT_ERROR(parseDescriptor(str.begin(), str.end()));

    str = "T";
    ASSERT_ERROR(parseDescriptor(str.begin(), str.end()));

    str = "Ljava.lang.Object";
    ASSERT_ERROR(parseDescriptor(str.begin(), str.end()));
}

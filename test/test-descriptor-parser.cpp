#include "test.hpp"

#include "../src/descriptor-parser.hpp"


void testDescriptorParser()
{
    std::string str = "BCDFIJLjava/lang/Object;SZV[B[[B";
    auto it = str.begin();

    ASSERT_TRUE(parseDescriptor(it, str.end()) == Type::tByte());
    ASSERT_TRUE(parseDescriptor(it, str.end()) == Type::tChar());
    ASSERT_TRUE(parseDescriptor(it, str.end()) == Type::tDouble());
    ASSERT_TRUE(parseDescriptor(it, str.end()) == Type::tFloat());
    ASSERT_TRUE(parseDescriptor(it, str.end()) == Type::tInt());
    ASSERT_TRUE(parseDescriptor(it, str.end()) == Type::tLong());
    ASSERT_TRUE(parseDescriptor(it, str.end()) == Type::tObject("java.lang.Object"));
    ASSERT_TRUE(parseDescriptor(it, str.end()) == Type::tShort());
    ASSERT_TRUE(parseDescriptor(it, str.end()) == Type::tBoolean());
    ASSERT_TRUE(parseDescriptor(it, str.end()) == Type::tVoid());
    ASSERT_TRUE(parseDescriptor(it, str.end()) == Type::tByte(1));
    ASSERT_TRUE(parseDescriptor(it, str.end()) == Type::tByte(2));

    str = "[[[";
    it = str.begin();
    ASSERT_ERROR(parseDescriptor(it, str.end()));

    str = "[[[T";
    it = str.begin();
    ASSERT_ERROR(parseDescriptor(it, str.end()));

    str = "T";
    it = str.begin();
    ASSERT_ERROR(parseDescriptor(it, str.end()));

    str = "Ljava.lang.Object";
    it = str.begin();
    ASSERT_ERROR(parseDescriptor(it, str.end()));
}

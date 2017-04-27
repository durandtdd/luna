#include "catch/catch.hpp"

#include "../src/java-class-file/descriptor-parser.hpp"


TEST_CASE("Descriptor parsing")
{
    std::string str = "BCDFIJLjava/lang/Object;SZV[B[[B";
    auto it = str.begin();

    REQUIRE(parseDescriptor(it, str.end()) == Type::tByte());
    REQUIRE(parseDescriptor(it, str.end()) == Type::tChar());
    REQUIRE(parseDescriptor(it, str.end()) == Type::tDouble());
    REQUIRE(parseDescriptor(it, str.end()) == Type::tFloat());
    REQUIRE(parseDescriptor(it, str.end()) == Type::tInt());
    REQUIRE(parseDescriptor(it, str.end()) == Type::tLong());
    REQUIRE(parseDescriptor(it, str.end()) == Type::tObject("java.lang.Object"));
    REQUIRE(parseDescriptor(it, str.end()) == Type::tShort());
    REQUIRE(parseDescriptor(it, str.end()) == Type::tBoolean());
    REQUIRE(parseDescriptor(it, str.end()) == Type::tVoid());
    REQUIRE(parseDescriptor(it, str.end()) == Type::tByte(1));
    REQUIRE(parseDescriptor(it, str.end()) == Type::tByte(2));

    str = "[[[";
    REQUIRE_THROWS(parseDescriptor(str.begin(), str.end()));

    str = "[[[T";
    REQUIRE_THROWS(parseDescriptor(str.begin(), str.end()));

    str = "T";
    REQUIRE_THROWS(parseDescriptor(str.begin(), str.end()));

    str = "Ljava.lang.Object";
    it = str.begin();
    REQUIRE_THROWS(parseDescriptor(it, str.end()));
}


TEST_CASE("Method descriptor parsing")
{
    std::string str = "()V";
    auto parsed = parseMethodDescriptor(str.begin(), str.end());

    REQUIRE(parsed.type == Type::tVoid());
    REQUIRE(parsed.parameters.size() == 0);

    str = "([[[DLjava.lang.Object;)Ljava.lang.Object;";
    parsed = parseMethodDescriptor(str.begin(), str.end());

    REQUIRE(parsed.type == Type::tObject("java.lang.Object"));
    REQUIRE(parsed.parameters.size() == 2);
    REQUIRE(parsed.parameters[0].type == Type::tDouble(3));
    REQUIRE(parsed.parameters[1].type == Type::tObject("java.lang.Object"));

    str = "()";
    REQUIRE_THROWS(parseDescriptor(str.begin(), str.end()));

    str = "(V";
    REQUIRE_THROWS(parseDescriptor(str.begin(), str.end()));
}

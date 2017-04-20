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
    it = str.begin();
    REQUIRE_THROWS(parseDescriptor(it, str.end()));

    str = "[[[T";
    it = str.begin();
    REQUIRE_THROWS(parseDescriptor(it, str.end()));

    str = "T";
    it = str.begin();
    REQUIRE_THROWS(parseDescriptor(it, str.end()));

    str = "Ljava.lang.Object";
    it = str.begin();
    REQUIRE_THROWS(parseDescriptor(it, str.end()));
}

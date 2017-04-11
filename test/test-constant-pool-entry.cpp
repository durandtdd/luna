#include "catch/catch.hpp"

#include "../src/constant-pool-entry.hpp"


TEST_CASE("Constant pool entry")
{
    ConstantPoolEntry entry(ConstantPoolEntry::Invalid);

    entry.setType(ConstantPoolEntry::Integer);
    entry.setData(0xdeadbeef);
    REQUIRE(entry.data() == 0xdeadbeef);

    entry.setType(ConstantPoolEntry::NameAndType);
    entry.setIndex1(0x0001);
    entry.setIndex2(0x0002);
    REQUIRE(entry.index1() == 0x0001);
    REQUIRE(entry.index2() == 0x0002);


    REQUIRE(ConstantPoolEntry::typeFromInt(0x00) == ConstantPoolEntry::Invalid);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x01) == ConstantPoolEntry::Utf8);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x02) == ConstantPoolEntry::Invalid);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x03) == ConstantPoolEntry::Integer);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x04) == ConstantPoolEntry::Float);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x05) == ConstantPoolEntry::Long);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x06) == ConstantPoolEntry::Double);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x07) == ConstantPoolEntry::Class);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x08) == ConstantPoolEntry::String);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x09) == ConstantPoolEntry::FieldRef);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x0a) == ConstantPoolEntry::MethodRef);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x0b) == ConstantPoolEntry::InterfaceMethodRef);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x0c) == ConstantPoolEntry::NameAndType);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x0d) == ConstantPoolEntry::Invalid);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x0e) == ConstantPoolEntry::Invalid);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x0f) == ConstantPoolEntry::MethodHandle);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x10) == ConstantPoolEntry::MethodType);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x11) == ConstantPoolEntry::Invalid);
    REQUIRE(ConstantPoolEntry::typeFromInt(0x12) == ConstantPoolEntry::InvokeDynamic);
    REQUIRE(ConstantPoolEntry::typeFromInt(0xff) == ConstantPoolEntry::Invalid);
}

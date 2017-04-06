#include "test.hpp"

#include "../src/constant-pool-entry.hpp"


void testConstantPoolEntry()
{
    ConstantPoolEntry entry(ConstantPoolEntry::Invalid);

    entry.setType(ConstantPoolEntry::Integer);
    entry.setData(0xdeadbeef);
    ASSERT_EQUAL(entry.data(), 0xdeadbeef);

    entry.setType(ConstantPoolEntry::NameAndType);
    entry.setIndex1(0x0001);
    entry.setIndex2(0x0002);
    ASSERT_EQUAL(entry.index1(), 0x0001);
    ASSERT_EQUAL(entry.index2(), 0x0002);


    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x00), ConstantPoolEntry::Invalid);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x01), ConstantPoolEntry::Utf8);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x02), ConstantPoolEntry::Invalid);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x03), ConstantPoolEntry::Integer);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x04), ConstantPoolEntry::Float);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x05), ConstantPoolEntry::Long);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x06), ConstantPoolEntry::Double);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x07), ConstantPoolEntry::Class);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x08), ConstantPoolEntry::String);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x09), ConstantPoolEntry::FieldRef);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x0a), ConstantPoolEntry::MethodRef);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x0b), ConstantPoolEntry::InterfaceMethodRef);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x0c), ConstantPoolEntry::NameAndType);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x0d), ConstantPoolEntry::Invalid);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x0e), ConstantPoolEntry::Invalid);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x0f), ConstantPoolEntry::MethodHandle);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x10), ConstantPoolEntry::MethodType);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x11), ConstantPoolEntry::Invalid);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0x12), ConstantPoolEntry::InvokeDynamic);
    ASSERT_EQUAL(ConstantPoolEntry::typeFromInt(0xff), ConstantPoolEntry::Invalid);
}

#include "test.hpp"

#include "../src/constant-pool.hpp"


void testConstantPool()
{
    ConstantPool cp;
    ConstantPoolEntry entry(ConstantPoolEntry::Invalid);

    entry = ConstantPoolEntry(ConstantPoolEntry::Class);
    entry.setIndex1(2);
    cp.addEntry(entry);

    entry = ConstantPoolEntry(ConstantPoolEntry::Double);
    double v = 3.1415;
    entry.setData(*reinterpret_cast<uint64*>(&v));
    cp.addEntry(entry);

    entry = ConstantPoolEntry(ConstantPoolEntry::Utf8);
    entry.setIndex1(0);
    cp.addEntry(entry);
    cp.addString("String 0");

    entry = ConstantPoolEntry(ConstantPoolEntry::Utf8);
    entry.setIndex1(1);
    cp.addEntry(entry);
    cp.addString("String 1");

    ASSERT_EQUAL(cp[0].index1(), 2);
    uint64 d = cp[1].data();
    ASSERT_EQUAL(*reinterpret_cast<double*>(&d), v);
    ASSERT_EQUAL(cp[2].index1(), 0);
    ASSERT_EQUAL(cp.string(2), "String 0");
    ASSERT_EQUAL(cp[3].index1(), 1);
    ASSERT_EQUAL(cp.string(3), "String 1");
    ASSERT_EQUAL(cp.size(), 4);
    ASSERT_EQUAL(cp.stringsSize(), 2);

    ASSERT_ERROR(cp[4]);
    ASSERT_ERROR(cp.string(4));
    ASSERT_ERROR(cp.string(0));
    cp[3].setIndex1(2);
    ASSERT_ERROR(cp.string(3));
}

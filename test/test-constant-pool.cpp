#include "catch/catch.hpp"

#include "../src/java-class-file/constant-pool.hpp"


TEST_CASE("Constant pool")
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

    REQUIRE(cp[0].index1() == 2);
    uint64 d = cp[1].data();
    REQUIRE(*reinterpret_cast<double*>(&d) == v);
    REQUIRE(cp[2].index1() == 0);
    REQUIRE(cp.string(2) == "String 0");
    REQUIRE(cp[3].index1() == 1);
    REQUIRE(cp.string(3) == "String 1");
    REQUIRE(cp.size() == 4);
    REQUIRE(cp.stringsSize() == 2);

    REQUIRE_THROWS(cp[4]);
    REQUIRE_THROWS(cp.string(4));
    REQUIRE_THROWS(cp.string(0));
    cp[3].setIndex1(2);
    REQUIRE_THROWS(cp.string(3));
}

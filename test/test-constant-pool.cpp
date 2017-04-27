#include "catch/catch.hpp"

#include <cmath>

#include "../src/java-class-file/constant-pool.hpp"


TEST_CASE("Constant pool")
{
    ConstantPool cp;
    ConstantPoolEntry cpe(ConstantPoolEntry::Invalid);

    cpe = ConstantPoolEntry(ConstantPoolEntry::Utf8);
    cpe.setIndex1(0);
    cp.addEntry(cpe);
    cp.addString("[[[D");

    cpe = ConstantPoolEntry(ConstantPoolEntry::Utf8);
    cpe.setIndex1(1);
    cp.addEntry(cpe);
    cp.addString("java/lang/Object");

    cpe = ConstantPoolEntry(ConstantPoolEntry::Utf8);
    cpe.setIndex1(2);
    cp.addEntry(cpe);
    cp.addString("Ljava/lang/Object;");

    cpe = ConstantPoolEntry(ConstantPoolEntry::Utf8);
    cpe.setIndex1(3);
    cp.addEntry(cpe);
    cp.addString("(I)V");

    cpe = ConstantPoolEntry(ConstantPoolEntry::Utf8);
    cpe.setIndex1(4);
    cp.addEntry(cpe);
    cp.addString("name");

    cpe = ConstantPoolEntry(ConstantPoolEntry::Class);
    cpe.setIndex1(0);
    cp.addEntry(cpe);

    cpe = ConstantPoolEntry(ConstantPoolEntry::Class);
    cpe.setIndex1(1);
    cp.addEntry(cpe);

    cpe = ConstantPoolEntry(ConstantPoolEntry::Class);
    cpe.setIndex1(2);
    cp.addEntry(cpe);

    cpe = ConstantPoolEntry(ConstantPoolEntry::NameAndType);
    cpe.setIndex1(4);
    cpe.setIndex2(0);
    cp.addEntry(cpe);

    cpe = ConstantPoolEntry(ConstantPoolEntry::NameAndType);
    cpe.setIndex1(4);
    cpe.setIndex2(3);
    cp.addEntry(cpe);

    cpe = ConstantPoolEntry(ConstantPoolEntry::FieldRef);
    cpe.setIndex1(6);
    cpe.setIndex2(8);
    cp.addEntry(cpe);

    cpe = ConstantPoolEntry(ConstantPoolEntry::MethodRef);
    cpe.setIndex1(6);
    cpe.setIndex2(9);
    cp.addEntry(cpe);

    cpe = ConstantPoolEntry(ConstantPoolEntry::InterfaceMethodRef);
    cpe.setIndex1(6);
    cpe.setIndex2(9);
    cp.addEntry(cpe);

    cpe = ConstantPoolEntry(ConstantPoolEntry::String);
    cpe.setIndex1(3);
    cp.addEntry(cpe);

    cpe = ConstantPoolEntry(ConstantPoolEntry::Integer);
    cpe.setData(0xffffffff);
    cp.addEntry(cpe);

    cpe = ConstantPoolEntry(ConstantPoolEntry::Long);
    cpe.setData(0xffffffffffffffff);
    cp.addEntry(cpe);

    cpe = ConstantPoolEntry(ConstantPoolEntry::Float);
    cpe.setData(0x3fcf1aa0);
    cp.addEntry(cpe);

    cpe = ConstantPoolEntry(ConstantPoolEntry::Double);
    cpe.setData(0x3ff9e353f7ced917);
    cp.addEntry(cpe);


    REQUIRE(cp.getString(0) == "[[[D");
    REQUIRE(cp.getString(1) == "java/lang/Object");
    REQUIRE(cp.getString(2) == "Ljava/lang/Object;");
    REQUIRE(cp.getString(3) == "(I)V");
    REQUIRE(cp.getString(4) == "name");
    REQUIRE(cp.getRef(5)->str() == "double[][][]");
    REQUIRE(cp.getRef(6)->str() == "java.lang.Object");
    REQUIRE(cp.getRef(7)->str() == "java.lang.Object");
    REQUIRE(cp[8].type() == ConstantPoolEntry::NameAndType);
    REQUIRE(cp[9].type() == ConstantPoolEntry::NameAndType);
    REQUIRE(cp.getRef(10)->str() == "double[][][] java.lang.Object.name");
    REQUIRE(cp.getRef(11)->str() == "void java.lang.Object.name(int param0)");
    REQUIRE(cp.getRef(12)->str() == "void java.lang.Object.name(int param0)");
    REQUIRE(cp.getString(13) == "(I)V");
    REQUIRE(cp.getInt(14) == -1);
    REQUIRE(cp.getInt(15) == -1);
    REQUIRE(std::abs(cp.getDouble(16)-1.618) < 0.0001);
    REQUIRE(std::abs(cp.getDouble(17)-1.618) < 0.0001);

    REQUIRE_THROWS(cp.getString(5));
    REQUIRE_THROWS(cp.getRef(0));
    REQUIRE_THROWS(cp.getInt(0));
    REQUIRE_THROWS(cp.getDouble(0));
    REQUIRE_THROWS(cp[18]);
}

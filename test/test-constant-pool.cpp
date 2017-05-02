#include "catch/catch.hpp"

#include <cmath>

#include "../src/java-class-file/constant-pool.hpp"


TEST_CASE("Constant pool")
{
    ConstantPool cp;

    cp.addString("[[[D");
    cp.addString("java/lang/Object");
    cp.addString("Ljava/lang/Object;");
    cp.addString("(I)V");
    cp.addString("name");

    /*  0 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::Utf8, 0, 0));
    /*  1 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::Utf8, 1, 0));
    /*  2 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::Utf8, 2, 0));
    /*  3 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::Utf8, 3, 0));
    /*  4 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::Utf8, 4, 0));
    /*  5 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::Class, 0, 0));
    /*  6 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::Class, 1, 0));
    /*  7 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::Class, 2, 0));
    /*  8 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::NameAndType, 4, 0));
    /*  9 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::NameAndType, 4, 3));
    /* 10 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::FieldRef, 6, 8));
    /* 11 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::MethodRef, 6, 9));
    /* 12 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::InterfaceMethodRef, 6, 9));
    /* 13 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::String, 3, 0));
    /* 14 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::Integer, 0xffffffff));
    /* 15 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::Long, 0xffffffffffffffff));
    /* 16 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::Invalid));
    /* 17 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::Float, 0x3fcf1aa0));
    /* 18 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::Double, 0x3ff9e353f7ced917));
    /* 19 */ cp.addEntry(ConstantPoolEntry(ConstantPoolEntry::Invalid));


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
    REQUIRE(std::abs(cp.getDouble(17)-1.618) < 0.0001);
    REQUIRE(std::abs(cp.getDouble(18)-1.618) < 0.0001);

    REQUIRE_THROWS(cp.getString(5));
    REQUIRE_THROWS(cp.getRef(0));
    REQUIRE_THROWS(cp.getInt(0));
    REQUIRE_THROWS(cp.getDouble(0));
    REQUIRE_THROWS(cp[20]);
}

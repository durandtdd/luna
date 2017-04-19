#include "catch/catch.hpp"

#include "../src/decoder/decoder.hpp"
#include "../src/utils.hpp"


TEST_CASE("Operands")
{
    Operand operand(Operand::UINT32, 0xffffffff);
    REQUIRE(operand.to<int8>() == -1);
    REQUIRE(operand.to<uint8>() == 255);
    REQUIRE(operand.to<int16>() == -1);
    REQUIRE(operand.to<uint16>() == 65535);
    REQUIRE(operand.to<int32>() == -1);
    REQUIRE(operand.to<uint32>() == 4294967295);


    operand.setType(Operand::INT8);
    REQUIRE(operand.get() == -1);

    operand.setType(Operand::UINT8);
    REQUIRE(operand.get() == 255);

    operand.setType(Operand::INT16);
    REQUIRE(operand.get() == -1);

    operand.setType(Operand::UINT16);
    REQUIRE(operand.get() == 65535);

    operand.setType(Operand::INT32);
    REQUIRE(operand.get() == -1);

    operand.setType(Operand::UINT32);
    REQUIRE(operand.get() == 4294967295);


    operand.from<int8>(-128);
    REQUIRE(operand.to<int8>() == -128);

    operand.from<uint8>(128);
    REQUIRE(operand.to<uint8>() == 128);

    operand.from<int16>(-32768);
    REQUIRE(operand.to<int16>() == -32768);

    operand.from<uint16>(32768);
    REQUIRE(operand.to<uint16>() == 32768);

    operand.from<int32>(-2147483648);
    REQUIRE(operand.to<int32>() == -2147483648);

    operand.from<uint32>(2147483648);
    REQUIRE(operand.to<uint32>() == 2147483648);
}


TEST_CASE("Decoder bytecodes")
{
    Decoder decoder;
    Instruction inst;

    inst = decoder.decode(stringToBytes("32"))[0];
    REQUIRE(inst.mnemonic == AALOAD);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("53"))[0];
    REQUIRE(inst.mnemonic == AASTORE);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("01"))[0];
    REQUIRE(inst.mnemonic == ACONST_NULL);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("19ff"))[0];
    REQUIRE(inst.mnemonic == ALOAD);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 255);

    inst = decoder.decode(stringToBytes("2a"))[0];
    REQUIRE(inst.mnemonic == ALOAD_0);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("2b"))[0];
    REQUIRE(inst.mnemonic == ALOAD_1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("2c"))[0];
    REQUIRE(inst.mnemonic == ALOAD_2);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("2d"))[0];
    REQUIRE(inst.mnemonic == ALOAD_3);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("bdffff"))[0];
    REQUIRE(inst.mnemonic == ANEWARRAY);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 65535);

    inst = decoder.decode(stringToBytes("b0"))[0];
    REQUIRE(inst.mnemonic == ARETURN);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("be"))[0];
    REQUIRE(inst.mnemonic == ARRAYLENGTH);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("3aff"))[0];
    REQUIRE(inst.mnemonic == ASTORE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 255);

    inst = decoder.decode(stringToBytes("4b"))[0];
    REQUIRE(inst.mnemonic == ASTORE_0);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("4c"))[0];
    REQUIRE(inst.mnemonic == ASTORE_1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("4d"))[0];
    REQUIRE(inst.mnemonic == ASTORE_2);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("4e"))[0];
    REQUIRE(inst.mnemonic == ASTORE_3);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("bf"))[0];
    REQUIRE(inst.mnemonic == ATHROW);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("33"))[0];
    REQUIRE(inst.mnemonic == BALOAD);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("54"))[0];
    REQUIRE(inst.mnemonic == BASTORE);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("10ff"))[0];
    REQUIRE(inst.mnemonic == BIPUSH);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("34"))[0];
    REQUIRE(inst.mnemonic == CALOAD);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("55"))[0];
    REQUIRE(inst.mnemonic == CASTORE);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("c0ffff"))[0];
    REQUIRE(inst.mnemonic == CHECKCAST);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 65535);

    inst = decoder.decode(stringToBytes("90"))[0];
    REQUIRE(inst.mnemonic == D2F);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("8e"))[0];
    REQUIRE(inst.mnemonic == D2I);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("8f"))[0];
    REQUIRE(inst.mnemonic == D2L);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("63"))[0];
    REQUIRE(inst.mnemonic == DADD);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("31"))[0];
    REQUIRE(inst.mnemonic == DALOAD);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("52"))[0];
    REQUIRE(inst.mnemonic == DASTORE);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("98"))[0];
    REQUIRE(inst.mnemonic == DCMPG);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("97"))[0];
    REQUIRE(inst.mnemonic == DCMPL);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("0e"))[0];
    REQUIRE(inst.mnemonic == DCONST_0);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("0f"))[0];
    REQUIRE(inst.mnemonic == DCONST_1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("6f"))[0];
    REQUIRE(inst.mnemonic == DDIV);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("18ff"))[0];
    REQUIRE(inst.mnemonic == DLOAD);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 255);

    inst = decoder.decode(stringToBytes("26"))[0];
    REQUIRE(inst.mnemonic == DLOAD_0);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("27"))[0];
    REQUIRE(inst.mnemonic == DLOAD_1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("28"))[0];
    REQUIRE(inst.mnemonic == DLOAD_2);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("29"))[0];
    REQUIRE(inst.mnemonic == DLOAD_3);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("6b"))[0];
    REQUIRE(inst.mnemonic == DMUL);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("77"))[0];
    REQUIRE(inst.mnemonic == DNEG);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("73"))[0];
    REQUIRE(inst.mnemonic == DREM);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("af"))[0];
    REQUIRE(inst.mnemonic == DRETURN);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("39ff"))[0];
    REQUIRE(inst.mnemonic == DSTORE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 255);

    inst = decoder.decode(stringToBytes("47"))[0];
    REQUIRE(inst.mnemonic == DSTORE_0);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("48"))[0];
    REQUIRE(inst.mnemonic == DSTORE_1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("49"))[0];
    REQUIRE(inst.mnemonic == DSTORE_2);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("4a"))[0];
    REQUIRE(inst.mnemonic == DSTORE_3);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("67"))[0];
    REQUIRE(inst.mnemonic == DSUB);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("59"))[0];
    REQUIRE(inst.mnemonic == DUP);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("5a"))[0];
    REQUIRE(inst.mnemonic == DUP_X1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("5b"))[0];
    REQUIRE(inst.mnemonic == DUP_X2);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("5c"))[0];
    REQUIRE(inst.mnemonic == DUP2);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("5d"))[0];
    REQUIRE(inst.mnemonic == DUP2_X1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("5e"))[0];
    REQUIRE(inst.mnemonic == DUP2_X2);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("8d"))[0];
    REQUIRE(inst.mnemonic == F2D);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("8b"))[0];
    REQUIRE(inst.mnemonic == F2I);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("8c"))[0];
    REQUIRE(inst.mnemonic == F2L);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("62"))[0];
    REQUIRE(inst.mnemonic == FADD);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("30"))[0];
    REQUIRE(inst.mnemonic == FALOAD);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("51"))[0];
    REQUIRE(inst.mnemonic == FASTORE);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("96"))[0];
    REQUIRE(inst.mnemonic == FCMPG);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("95"))[0];
    REQUIRE(inst.mnemonic == FCMPL);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("0b"))[0];
    REQUIRE(inst.mnemonic == FCONST_0);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("0c"))[0];
    REQUIRE(inst.mnemonic == FCONST_1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("0d"))[0];
    REQUIRE(inst.mnemonic == FCONST_2);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("6e"))[0];
    REQUIRE(inst.mnemonic == FDIV);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("17ff"))[0];
    REQUIRE(inst.mnemonic == FLOAD);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 255);

    inst = decoder.decode(stringToBytes("22"))[0];
    REQUIRE(inst.mnemonic == FLOAD_0);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("23"))[0];
    REQUIRE(inst.mnemonic == FLOAD_1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("24"))[0];
    REQUIRE(inst.mnemonic == FLOAD_2);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("25"))[0];
    REQUIRE(inst.mnemonic == FLOAD_3);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("6a"))[0];
    REQUIRE(inst.mnemonic == FMUL);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("76"))[0];
    REQUIRE(inst.mnemonic == FNEG);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("72"))[0];
    REQUIRE(inst.mnemonic == FREM);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("ae"))[0];
    REQUIRE(inst.mnemonic == FRETURN);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("38ff"))[0];
    REQUIRE(inst.mnemonic == FSTORE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 255);

    inst = decoder.decode(stringToBytes("43"))[0];
    REQUIRE(inst.mnemonic == FSTORE_0);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("44"))[0];
    REQUIRE(inst.mnemonic == FSTORE_1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("45"))[0];
    REQUIRE(inst.mnemonic == FSTORE_2);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("46"))[0];
    REQUIRE(inst.mnemonic == FSTORE_3);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("66"))[0];
    REQUIRE(inst.mnemonic == FSUB);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("b4ffff"))[0];
    REQUIRE(inst.mnemonic == GETFIELD);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 65535);

    inst = decoder.decode(stringToBytes("b2ffff"))[0];
    REQUIRE(inst.mnemonic == GETSTATIC);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 65535);

    inst = decoder.decode(stringToBytes("a7ffff"))[0];
    REQUIRE(inst.mnemonic == GOTO);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("c8ffffffff"))[0];
    REQUIRE(inst.mnemonic == GOTO_W);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("91"))[0];
    REQUIRE(inst.mnemonic == I2B);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("92"))[0];
    REQUIRE(inst.mnemonic == I2C);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("87"))[0];
    REQUIRE(inst.mnemonic == I2D);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("86"))[0];
    REQUIRE(inst.mnemonic == I2F);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("85"))[0];
    REQUIRE(inst.mnemonic == I2L);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("93"))[0];
    REQUIRE(inst.mnemonic == I2S);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("60"))[0];
    REQUIRE(inst.mnemonic == IADD);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("2e"))[0];
    REQUIRE(inst.mnemonic == IALOAD);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("7e"))[0];
    REQUIRE(inst.mnemonic == IAND);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("4f"))[0];
    REQUIRE(inst.mnemonic == IASTORE);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("02"))[0];
    REQUIRE(inst.mnemonic == ICONST_M1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("03"))[0];
    REQUIRE(inst.mnemonic == ICONST_0);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("04"))[0];
    REQUIRE(inst.mnemonic == ICONST_1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("05"))[0];
    REQUIRE(inst.mnemonic == ICONST_2);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("06"))[0];
    REQUIRE(inst.mnemonic == ICONST_3);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("07"))[0];
    REQUIRE(inst.mnemonic == ICONST_4);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("08"))[0];
    REQUIRE(inst.mnemonic == ICONST_5);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("6c"))[0];
    REQUIRE(inst.mnemonic == IDIV);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("a5ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ACMPEQ);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a6ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ACMPNE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("9fffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPEQ);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a0ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPNE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a1ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPLT);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a2ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPGE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a3ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPGT);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a4ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPLE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("99ffff"))[0];
    REQUIRE(inst.mnemonic == IFEQ);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("9affff"))[0];
    REQUIRE(inst.mnemonic == IFNE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("9bffff"))[0];
    REQUIRE(inst.mnemonic == IFLT);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("9cffff"))[0];
    REQUIRE(inst.mnemonic == IFGE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("9dffff"))[0];
    REQUIRE(inst.mnemonic == IFGT);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("9effff"))[0];
    REQUIRE(inst.mnemonic == IFLE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("9fffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPEQ);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a0ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPNE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a1ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPLT);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a2ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPGE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a3ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPGT);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a4ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPLE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("9fffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPEQ);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a0ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPNE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a1ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPLT);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a2ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPGE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("c7ffff"))[0];
    REQUIRE(inst.mnemonic == IFNONNULL);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("c6ffff"))[0];
    REQUIRE(inst.mnemonic == IFNULL);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("9fffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPEQ);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a0ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPNE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a1ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPLT);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a2ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPGE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("a3ffff"))[0];
    REQUIRE(inst.mnemonic == IF_ICMPGT);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("84ffff"))[0];
    REQUIRE(inst.mnemonic == IINC);
    REQUIRE(inst.operands.size() == 2);
    REQUIRE(inst.operands[0].get() == 255);
    REQUIRE(inst.operands[1].get() == -1);

    inst = decoder.decode(stringToBytes("15ff"))[0];
    REQUIRE(inst.mnemonic == ILOAD);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 255);

    inst = decoder.decode(stringToBytes("1a"))[0];
    REQUIRE(inst.mnemonic == ILOAD_0);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("1b"))[0];
    REQUIRE(inst.mnemonic == ILOAD_1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("1c"))[0];
    REQUIRE(inst.mnemonic == ILOAD_2);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("1d"))[0];
    REQUIRE(inst.mnemonic == ILOAD_3);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("68"))[0];
    REQUIRE(inst.mnemonic == IMUL);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("74"))[0];
    REQUIRE(inst.mnemonic == INEG);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("c1ffff"))[0];
    REQUIRE(inst.mnemonic == INSTANCEOF);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 65535);

    inst = decoder.decode(stringToBytes("baffff0000"))[0];
    REQUIRE(inst.mnemonic == INVOKEDYNAMIC);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 65535);

    inst = decoder.decode(stringToBytes("b9ffffff00"))[0];
    REQUIRE(inst.mnemonic == INVOKEINTERFACE);
    REQUIRE(inst.operands.size() == 2);
    REQUIRE(inst.operands[0].get() == 65535);
    REQUIRE(inst.operands[1].get() == 255);

    inst = decoder.decode(stringToBytes("b7ffff"))[0];
    REQUIRE(inst.mnemonic == INVOKESPECIAL);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 65535);

    inst = decoder.decode(stringToBytes("b8ffff"))[0];
    REQUIRE(inst.mnemonic == INVOKESTATIC);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 65535);

    inst = decoder.decode(stringToBytes("b6ffff"))[0];
    REQUIRE(inst.mnemonic == INVOKEVIRTUAL);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 65535);

    inst = decoder.decode(stringToBytes("80"))[0];
    REQUIRE(inst.mnemonic == IOR);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("70"))[0];
    REQUIRE(inst.mnemonic == IREM);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("ac"))[0];
    REQUIRE(inst.mnemonic == IRETURN);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("78"))[0];
    REQUIRE(inst.mnemonic == ISHL);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("7a"))[0];
    REQUIRE(inst.mnemonic == ISHR);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("36ff"))[0];
    REQUIRE(inst.mnemonic == ISTORE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 255);

    inst = decoder.decode(stringToBytes("3b"))[0];
    REQUIRE(inst.mnemonic == ISTORE_0);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("3c"))[0];
    REQUIRE(inst.mnemonic == ISTORE_1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("3d"))[0];
    REQUIRE(inst.mnemonic == ISTORE_2);;
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("3e"))[0];
    REQUIRE(inst.mnemonic == ISTORE_3);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("64"))[0];
    REQUIRE(inst.mnemonic == ISUB);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("7c"))[0];
    REQUIRE(inst.mnemonic == IUSHR);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("82"))[0];
    REQUIRE(inst.mnemonic == IXOR);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("a8ffff"))[0];
    REQUIRE(inst.mnemonic == JSR);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("c9ffffffff"))[0];
    REQUIRE(inst.mnemonic == JSR_W);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("8a"))[0];
    REQUIRE(inst.mnemonic == L2D);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("89"))[0];
    REQUIRE(inst.mnemonic == L2F);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("88"))[0];
    REQUIRE(inst.mnemonic == L2I);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("61"))[0];
    REQUIRE(inst.mnemonic == LADD);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("2f"))[0];
    REQUIRE(inst.mnemonic == LALOAD);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("7f"))[0];
    REQUIRE(inst.mnemonic == LAND);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("50"))[0];
    REQUIRE(inst.mnemonic == LASTORE);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("94"))[0];
    REQUIRE(inst.mnemonic == LCMP);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("09"))[0];
    REQUIRE(inst.mnemonic == LCONST_0);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("0a"))[0];
    REQUIRE(inst.mnemonic == LCONST_1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("12ff"))[0];
    REQUIRE(inst.mnemonic == LDC);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 255);

    inst = decoder.decode(stringToBytes("13ffff"))[0];
    REQUIRE(inst.mnemonic == LDC_W);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 65535);

    inst = decoder.decode(stringToBytes("14ffff"))[0];
    REQUIRE(inst.mnemonic == LDC2_W);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 65535);

    inst = decoder.decode(stringToBytes("6d"))[0];
    REQUIRE(inst.mnemonic == LDIV);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("16ff"))[0];
    REQUIRE(inst.mnemonic == LLOAD);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 255);

    inst = decoder.decode(stringToBytes("1e"))[0];
    REQUIRE(inst.mnemonic == LLOAD_0);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("1f"))[0];
    REQUIRE(inst.mnemonic == LLOAD_1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("20"))[0];
    REQUIRE(inst.mnemonic == LLOAD_2);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("21"))[0];
    REQUIRE(inst.mnemonic == LLOAD_3);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("69"))[0];
    REQUIRE(inst.mnemonic == LMUL);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("75"))[0];
    REQUIRE(inst.mnemonic == LNEG);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("00 ab 0000 00000012 00000003 fffffffffffffffe 0000000100000002 0000000200000004"))[1];
    REQUIRE(inst.mnemonic == LOOKUPSWITCH);
    REQUIRE(inst.operands.size() == 7);
    REQUIRE(inst.operands[0].get() == 18);
    REQUIRE(inst.operands[1].get() == -1);
    REQUIRE(inst.operands[2].get() == -2);
    REQUIRE(inst.operands[3].get() == 1);
    REQUIRE(inst.operands[4].get() == 2);
    REQUIRE(inst.operands[5].get() == 2);
    REQUIRE(inst.operands[6].get() == 4);

    inst = decoder.decode(stringToBytes("81"))[0];
    REQUIRE(inst.mnemonic == LOR);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("71"))[0];
    REQUIRE(inst.mnemonic == LREM);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("ad"))[0];
    REQUIRE(inst.mnemonic == LRETURN);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("79"))[0];
    REQUIRE(inst.mnemonic == LSHL);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("7b"))[0];
    REQUIRE(inst.mnemonic == LSHR);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("37ff"))[0];
    REQUIRE(inst.mnemonic == LSTORE);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 255);

    inst = decoder.decode(stringToBytes("3f"))[0];
    REQUIRE(inst.mnemonic == LSTORE_0);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("40"))[0];
    REQUIRE(inst.mnemonic == LSTORE_1);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("41"))[0];
    REQUIRE(inst.mnemonic == LSTORE_2);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("42"))[0];
    REQUIRE(inst.mnemonic == LSTORE_3);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("65"))[0];
    REQUIRE(inst.mnemonic == LSUB);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("7d"))[0];
    REQUIRE(inst.mnemonic == LUSHR);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("83"))[0];
    REQUIRE(inst.mnemonic == LXOR);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("c2"))[0];
    REQUIRE(inst.mnemonic == MONITORENTER);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("c3"))[0];
    REQUIRE(inst.mnemonic == MONITOREXIT);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("c5ffffff"))[0];
    REQUIRE(inst.mnemonic == MULTIANEWARRAY);
    REQUIRE(inst.operands.size() == 2);
    REQUIRE(inst.operands[0].get() == 65535);
    REQUIRE(inst.operands[1].get() == 255);

    inst = decoder.decode(stringToBytes("bbffff"))[0];
    REQUIRE(inst.mnemonic == NEW);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 65535);

    inst = decoder.decode(stringToBytes("bcff"))[0];
    REQUIRE(inst.mnemonic == NEWARRAY);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 255);

    inst = decoder.decode(stringToBytes("00"))[0];
    REQUIRE(inst.mnemonic == NOP);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("57"))[0];
    REQUIRE(inst.mnemonic == POP);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("58"))[0];
    REQUIRE(inst.mnemonic == POP2);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("b5ffff"))[0];
    REQUIRE(inst.mnemonic == PUTFIELD);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 65535);

    inst = decoder.decode(stringToBytes("b3ffff"))[0];
    REQUIRE(inst.mnemonic == PUTSTATIC);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 65535);

    inst = decoder.decode(stringToBytes("a9ff"))[0];
    REQUIRE(inst.mnemonic == RET);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 255);

    inst = decoder.decode(stringToBytes("b1"))[0];
    REQUIRE(inst.mnemonic == RETURN);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("35"))[0];
    REQUIRE(inst.mnemonic == SALOAD);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("56"))[0];
    REQUIRE(inst.mnemonic == SASTORE);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("11ffff"))[0];
    REQUIRE(inst.mnemonic == SIPUSH);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == -1);

    inst = decoder.decode(stringToBytes("5f"))[0];
    REQUIRE(inst.mnemonic == SWAP);
    REQUIRE(inst.operands.size() == 0);

    inst = decoder.decode(stringToBytes("000000aa 00000012 00000003 00000006 0000001 00000002 fffffffe ffffffff"))[3];
    REQUIRE(inst.mnemonic == TABLESWITCH);
    REQUIRE(inst.operands.size() == 7);
    REQUIRE(inst.operands[0].get() == 18);
    REQUIRE(inst.operands[1].get() == 3);
    REQUIRE(inst.operands[2].get() == 6);
    REQUIRE(inst.operands[3].get() == 1);
    REQUIRE(inst.operands[4].get() == 2);
    REQUIRE(inst.operands[5].get() == -2);
    REQUIRE(inst.operands[6].get() == -1);

    inst = decoder.decode(stringToBytes("c415ffff"))[0];
    REQUIRE(inst.mnemonic == ILOAD);
    REQUIRE(inst.operands.size() == 1);
    REQUIRE(inst.operands[0].get() == 65535);

    inst = decoder.decode(stringToBytes("c484ffffffff"))[0];
    REQUIRE(inst.mnemonic == IINC);
    REQUIRE(inst.operands.size() == 2);
    REQUIRE(inst.operands[0].get() == 65535);
    REQUIRE(inst.operands[1].get() == -1);
}


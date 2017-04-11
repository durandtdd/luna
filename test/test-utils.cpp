#include "catch/catch.hpp"

#include "../src/utils.hpp"

TEST_CASE("String to bytes")
{
    std::vector<uint8> bytes = stringToBytes("0123456789abcdef");
    REQUIRE(bytes[0] == 0x01);
    REQUIRE(bytes[1] == 0x23);
    REQUIRE(bytes[2] == 0x45);
    REQUIRE(bytes[3] == 0x67);
    REQUIRE(bytes[4] == 0x89);
    REQUIRE(bytes[5] == 0xab);
    REQUIRE(bytes[6] == 0xcd);
    REQUIRE(bytes[7] == 0xef);


    bytes = stringToBytes(" 0123  4567   89ab  cd  ef   ");
    REQUIRE(bytes[0] == 0x01);
    REQUIRE(bytes[1] == 0x23);
    REQUIRE(bytes[2] == 0x45);
    REQUIRE(bytes[3] == 0x67);
    REQUIRE(bytes[4] == 0x89);
    REQUIRE(bytes[5] == 0xab);
    REQUIRE(bytes[6] == 0xcd);
    REQUIRE(bytes[7] == 0xef);
}


TEST_CASE("Dump bytes to a string")
{
    std::vector<uint8> bytes = stringToBytes("000102030405060708090a0b0c0d0e0f1011121314151617");
    std::string out;
    std::string exp;

    out = dump(bytes);
    exp = "00000000   00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f   ................\n"
          "00000010   10 11 12 13 14 15 16 17                           ........        \n";
    REQUIRE(out == exp);

    out = dump(bytes, 8);
    exp = "00000008   08 09 0a 0b 0c 0d 0e 0f 10 11 12 13 14 15 16 17   ................\n";
    REQUIRE(out == exp);

    out = dump(bytes, 0, 8);
    exp = "00000000   00 01 02 03 04 05 06 07                           ........        \n";
    REQUIRE(out == exp);

    out = dump(std::vector<uint8>());
    exp = "";
    REQUIRE(out == exp);
}

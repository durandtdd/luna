#include "catch/catch.hpp"

#include "../src/streamreader.hpp"
#include "../src/utils.hpp"


TEST_CASE("Stream reader")
{
    std::vector<uint8> bytes = stringToBytes("000102030405060708090a0b0c0d0e0f");

    // Little endian
    StreamReader reader(bytes);
    REQUIRE(reader.size() == 16);
    REQUIRE(reader.read<uint8>() == 0x00);
    REQUIRE(reader.read<uint8>(false) == 0x01);
    REQUIRE(reader.read<uint8>() == 0x01);
    REQUIRE(reader.read<uint16>() == 0x0302);
    REQUIRE(reader.read<uint32>() == 0x07060504);
    uint64 u1 = 0x0f0e0d0c0b0a0908; // Workaround bug in Catch with uint64
    REQUIRE(reader.read<uint64>() == u1);
    REQUIRE(reader.eos() ==  true);
    REQUIRE_THROWS(reader.read<uint8>());
    reader.seekg(5);
    REQUIRE(reader.read<uint8>() == 0x05);
    REQUIRE(reader.tellg() == 6);
    REQUIRE(reader.eos() ==  false);
    reader.skip(5);
    REQUIRE(reader.read<uint8>() ==  0x0b);
    REQUIRE_THROWS(reader.read<uint64>());
    REQUIRE_THROWS(reader.skip(8));
    REQUIRE_THROWS(reader.seekg(17));

    // Big endian
    StreamReader readerbe(bytes, StreamReader::BigEndian);
    REQUIRE(readerbe.read<uint8>() == 0x00);
    REQUIRE(readerbe.read<uint8>(false) == 0x01);
    REQUIRE(readerbe.read<uint8>() == 0x01);
    REQUIRE(readerbe.read<uint16>() == 0x0203);
    REQUIRE(readerbe.read<uint32>() == 0x04050607);
    uint64 u2 = 0x08090a0b0c0d0e0f; // Workaround bug in Catch with uint64
    REQUIRE(readerbe.read<uint64>() == u2);
    REQUIRE(readerbe.eos() == true);
    REQUIRE_THROWS(readerbe.read<uint8>());
    readerbe.seekg(5);
    REQUIRE(readerbe.read<uint8>() == 0x05);
    REQUIRE(readerbe.tellg() == 6);
    REQUIRE(readerbe.eos() == false);
    readerbe.skip(5);
    REQUIRE(readerbe.read<uint8>() == 0x0b);
    REQUIRE_THROWS(readerbe.read<uint64>());
    REQUIRE_THROWS(readerbe.skip(8));
    REQUIRE_THROWS(readerbe.seekg(17));
}

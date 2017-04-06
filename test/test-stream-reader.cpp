#include "test.hpp"

#include "../src/streamreader.hpp"
#include "../src/utils.hpp"


void testStreamReader()
{
    std::vector<uint8> bytes = stringToBytes("000102030405060708090a0b0c0d0e0f");

    // Little endian
    StreamReader reader(bytes);
    ASSERT_EQUAL(reader.size(), 16);
    ASSERT_EQUAL(reader.read<uint8>(), 0x00);
    ASSERT_EQUAL(reader.read<uint8>(false), 0x01);
    ASSERT_EQUAL(reader.read<uint8>(), 0x01);
    ASSERT_EQUAL(reader.read<uint16>(), 0x0302);
    ASSERT_EQUAL(reader.read<uint32>(), 0x07060504);
    ASSERT_EQUAL(reader.read<uint64>(), 0x0f0e0d0c0b0a0908);
    ASSERT_EQUAL(reader.eos(), true);
    ASSERT_ERROR(reader.read<uint8>());
    reader.seekg(5);
    ASSERT_EQUAL(reader.read<uint8>(), 0x05);
    ASSERT_EQUAL(reader.tellg(), 6);
    ASSERT_EQUAL(reader.eos(), false);
    reader.skip(5);
    ASSERT_EQUAL(reader.read<uint8>(), 0x0b);
    ASSERT_ERROR(reader.read<uint64>());
    ASSERT_ERROR(reader.skip(8));
    ASSERT_ERROR(reader.seekg(17));

    // Big endian
    StreamReader readerbe(bytes, StreamReader::BigEndian);
    ASSERT_EQUAL(readerbe.read<uint8>(), 0x00);
    ASSERT_EQUAL(readerbe.read<uint8>(false), 0x01);
    ASSERT_EQUAL(readerbe.read<uint8>(), 0x01);
    ASSERT_EQUAL(readerbe.read<uint16>(), 0x0203);
    ASSERT_EQUAL(readerbe.read<uint32>(), 0x04050607);
    ASSERT_EQUAL(readerbe.read<uint64>(), 0x08090a0b0c0d0e0f);
    ASSERT_EQUAL(readerbe.eos(), true);
    ASSERT_ERROR(readerbe.read<uint8>());
    readerbe.seekg(5);
    ASSERT_EQUAL(readerbe.read<uint8>(), 0x05);
    ASSERT_EQUAL(readerbe.tellg(), 6);
    ASSERT_EQUAL(readerbe.eos(), false);
    readerbe.skip(5);
    ASSERT_EQUAL(readerbe.read<uint8>(), 0x0b);
    ASSERT_ERROR(readerbe.read<uint64>());
    ASSERT_ERROR(readerbe.skip(8));
    ASSERT_ERROR(readerbe.seekg(17));
}

#include "test.hpp"


int main()
{
    // Utils
    RUN_TEST(testStringToBytes);
    RUN_TEST(testDump);

    // StreamReader
    RUN_TEST(testStreamReader);

    // ConstantPoolEntry
    RUN_TEST(testConstantPoolEntry);

    // ConstantPool
    RUN_TEST(testConstantPool);

    // Type
    RUN_TEST(testType);

    // Descriptor parser
    RUN_TEST(testDescriptorParser);

    return 0;
}

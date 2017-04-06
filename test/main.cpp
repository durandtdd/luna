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

    return 0;
}

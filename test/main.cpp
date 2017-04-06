#include "test.hpp"


int main()
{
    // Utils
    RUN_TEST(testStringToBytes);
    RUN_TEST(testDump);

    // StreamReader
    RUN_TEST(testStreamReader);

    return 0;
}

#pragma once

#include <exception>
#include <iomanip>
#include <iostream>
#include <string>


class TestFail: public std::exception
{
public:
    TestFail(int line, std::string message)
    {
        m_msg = "[" + std::to_string(line) + "] " + message;
    }

    const char* what() const override
    {
        return m_msg.c_str();
    }

private:
    std::string m_msg;
};



#define ASSERT_TRUE(expr)\
    if(!(expr))\
        throw TestFail(__LINE__, #expr);

#define ASSERT_TRUE_MSG(expr, message)\
    if(!(expr))\
        throw TestFail(__LINE__, message);

#define ASSERT_EQUAL(expr1, expr2)\
    if(!(expr1 == expr2))\
        throw TestFail(__LINE__, #expr1 + std::string(" != ") + #expr2);

#define ASSERT_ERROR(expr)\
    try\
    {\
        expr;\
        throw TestFail(__LINE__, #expr);\
    }\
    catch(const std::exception&)\
    {}

#define FAIL(message)\
    throw TestFail(__LINE__, message);



#define RUN_TEST(name)\
    try\
    {\
        std::cout << "Running " << std::setw(30) << std::left << #name;\
        name();\
        std::cout << "OK" << std::endl;\
    }\
    catch(const TestFail& fail)\
    {\
        std::cout << "FAIL\n    " << fail.what() << std::endl;\
    }



/**
 * @brief Test the stringToBytes utils function
 */
void testStringToBytes();

/**
 * @brief Test the dump utils function
 */
void testDump();

/**
 * @brief Test the stream reader class
 */
void testStreamReader();

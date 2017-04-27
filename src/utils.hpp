#pragma once

#include <functional>
#include <string>
#include <type_traits>
#include <vector>

#include "common.hpp"


/**
 * @brief Convert a string of hex values to a byte array
 * @param hex String of hex values
 * @return Byte array
 */
std::vector<uint8> stringToBytes(const std::string& hex);


/**
* @brief Dump a byte array to a string [beg, end)
* @param bytes Bytes
* @param beg Index of first byte to dump
* @param end Index of last byte to dump + 1
* @return String of bytes
*/
std::string dump(const std::vector<uint8>& bytes, uint64 beg = 0, uint64 end = -1);


/**
 * @brief Join elements to a string
 * @param first Iterator on first element
 * @param last Iterator on last element
 * @param separator Separator
 * @param op Operation to apply to each element that return a string
 * @return Joined elements
 *
 * Example:
 *     struct S {char a; char b;}
 *
 *     std::vector<S> v = {{'a', 'b'}, {'c', 'd'}, {'e', 'f'}};
 *     std::string s = strjoin(v.begin(), v.end(), ", ", [](auto e) {return e.b;});
 *     // s == "a, c, e"
 */
template<typename InputIt>
std::string strjoin(InputIt first, InputIt last, const std::string& separator,
                    const std::function<std::string(typename InputIt::value_type)>& op)
{
    std::string str;

    while(first != last)
    {
        str += op(*first);

        if(++first != last)
            str += separator;
    }

    return str;
}


/**
 * @brief Join elements to a string
 * @param first Iterator on first element
 * @param last Iterator on last element
 * @param separator Separator
 * @return Joined elements
 *
 * Example:
 *     std::vector<std::string> v = {"a", "bc", "d"};
 *     std::string s = strjoin(v.begin(), v.end(), ", ", [](auto e) {return e.b;});
 *     // s == "a, bc, d"
 */
template<typename InputIt>
std::string strjoin(InputIt first, InputIt last, const std::string& separator)
{
    std::string str;

    while(first != last)
    {
        str += *first;

        if(++first != last)
            str += separator;
    }

    return str;
}

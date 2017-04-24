#pragma once

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
 * @brief Convert little endian bytes to float
 * @param bytes Bytes
 * @return Float
 */
float bytesToFloat(uint64 bytes);


/**
 * @brief Convert little endian bytes to double
 * @param bytes Bytes
 * @return Double
 */
double bytesToDouble(uint64 bytes);

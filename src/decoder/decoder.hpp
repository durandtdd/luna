#pragma once

#include <vector>

#include "../common.hpp"
#include "instruction.hpp"


/**
 * @brief Object used to decode bytecode to instructions
 */
class Decoder
{
public:
    /**
     * @brief Construct a Decoder
     */
    Decoder();

    /**
     * @brief Decode bytecode to instructions
     * @param bytes Bytes to decode
     * @return List of decoded instructions
     */
    std::vector<Instruction> decode(const std::vector<uint8>& bytes);
};

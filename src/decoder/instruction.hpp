#pragma once

#include <string>
#include <vector>

#include "../common.hpp"
#include "mnemonic.hpp"
#include "operand.hpp"


/**
 * @brief Structure representing a decoded instruction
 */
struct Instruction
{
public:
    /** Instruction name (nop, ldiv...) */
    Mnemonic mnemonic = INVALID;

    /** Operands (depends on instruction) */
    std::vector<Operand> operands;

    /** Instruction offset */
    uint32 offset = 0;


public:
    /**
     * @brief Convert instruction to a string representation
     * @return String
     */
    std::string str() const;
};

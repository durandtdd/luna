#pragma once

#include <vector>

#include "mnemonic.hpp"
#include "operand.hpp"


/**
 * @brief Structure describing the opcodes "templates"
 *
 * The structure holds the opcode name and the type of its operands encoded
 * in the bytecode
 */
struct Opcode
{
    /** Name */
    Mnemonic mnemonic = INVALID;

    /** Operands */
    std::vector<Operand::Type> operands;

    /** Table of all opcodes */
    static Opcode table[256];
};

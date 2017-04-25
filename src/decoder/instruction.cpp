#include "instruction.hpp"

#include <iomanip>
#include <sstream>

#include "../utils.hpp"


std::string Instruction::str() const
{
    std::ostringstream oss;

    // Offset
    oss << "/* " << std::setw(4) << std::setfill('0') << offset << " */ " << std::setw(0);

    // Mnemonic
    oss << ::str(mnemonic);

    // Operands
    if(operands.size() > 0)
        oss << " " << strjoin(operands.begin(), operands.end(), ", ", [](auto e){return std::to_string(e.get());});

    return oss.str();
}

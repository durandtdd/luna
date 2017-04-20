#include "instruction.hpp"

#include <iomanip>
#include <sstream>


std::string Instruction::str() const
{
    std::ostringstream oss;

    oss << "[" << std::setw(6) << std::setfill('0') << offset << "] ";

    oss << std::setw(0);
    oss << std::dec;

    oss << mnemonicStr(mnemonic);


    if(operands.size() > 0)
    {
        oss << " ";
        for(auto it = operands.begin(); it != operands.end(); ++it)
        {
            oss << it->get();

            if(it != operands.end()-1)
                oss << ", ";
        }
    }

    return oss.str();
}

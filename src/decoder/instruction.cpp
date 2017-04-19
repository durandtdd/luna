#include "instruction.hpp"

#include <sstream>


std::string Instruction::str() const
{
    std::ostringstream oss;

    oss << mnemonicStr(mnemonic);

    if(operands.size() > 0)
    {
        oss << " ";
        for(auto it = operands.begin(); it != operands.end(); ++it)
        {
            switch(it->type())
            {
                case Operand::INT8:
                    oss << (int64)it->to<int8>();
                    break;

                case Operand::UINT8:
                    oss << (int64)it->to<uint8>();
                    break;

                case Operand::INT16:
                    oss << (int64)it->to<int16>();
                    break;

                case Operand::UINT16:
                    oss << (int64)it->to<uint16>();
                    break;

                case Operand::INT32:
                    oss << (int64)it->to<int32>();
                    break;

                case Operand::UINT32:
                    oss << (int64)it->to<uint32>();
                    break;

                default:
                    break;
            }

            if(it != operands.end()-1)
                oss << ", ";
        }
    }

    return oss.str();
}

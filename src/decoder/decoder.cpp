#include "decoder.hpp"

#include "../streamreader.hpp"
#include "opcode.hpp"


Decoder::Decoder()
{
}


std::vector<Instruction> Decoder::decode(const std::vector<uint8>& bytes)
{
    StreamReader reader(bytes);
    std::vector<Instruction> instructions;

    // Decode instructions until end of stream
    while(!reader.eos())
    {
        Instruction instruction;

        // Get opcode "template"
        Opcode opcode = Opcode::table[reader.read<uint8>()];
        instruction.mnemonic = opcode.mnemonic;

        // Read operands
        for(Operand::Type type: opcode.operands)
        {
            switch(type)
            {
                case Operand::INT8:
                    instruction.operands.push_back(Operand(Operand::INT8));
                    instruction.operands.back().from<int8>(reader.read<int8>());
                    break;

                case Operand::UINT8:
                    instruction.operands.push_back(Operand(Operand::UINT8));
                    instruction.operands.back().from<uint8>(reader.read<uint8>());
                    break;

                case Operand::INT16:
                    instruction.operands.push_back(Operand(Operand::INT16));
                    instruction.operands.back().from<int16>(reader.read<int16>());
                    break;

                case Operand::UINT16:
                    instruction.operands.push_back(Operand(Operand::UINT16));
                    instruction.operands.back().from<uint16>(reader.read<uint16>());
                    break;

                case Operand::INT32:
                    instruction.operands.push_back(Operand(Operand::INT32));
                    instruction.operands.back().from<int32>(reader.read<int32>());
                    break;

                case Operand::UINT32:
                    instruction.operands.push_back(Operand(Operand::UINT32));
                    instruction.operands.back().from<uint32>(reader.read<uint32>());
                    break;

                case Operand::DUMMY:
                    reader.skip(1);
                    break;

                default:
                    break;
            }
        }

        // Save instruction
        instructions.push_back(instruction);
    }

    return instructions;
}

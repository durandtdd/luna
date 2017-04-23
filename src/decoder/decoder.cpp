#include "decoder.hpp"

#include "../streamreader.hpp"
#include "opcode.hpp"


Decoder::Decoder()
{
}


void readLookupSwitch(StreamReader& reader, std::vector<Operand>& operands)
{
    // Align to 4-byte boundary
    uint32 idx = reader.tellg();
    if(idx%4 != 0)
        idx += 4-idx%4;
    reader.seekg(idx);

    // Default
    Operand def(Operand::INT32, reader.read<int32>());
    operands.push_back(def);

    // Pairs
    int32 npairs = reader.read<int32>();
    for(int32 k=0; k<npairs; k++)
    {
        // Key
        Operand key(Operand::INT32, reader.read<int32>());
        operands.push_back(key);

        // Offset
        Operand offset(Operand::INT32, reader.read<int32>());
        operands.push_back(offset);
    }
}


void readTableSwitch(StreamReader& reader, std::vector<Operand>& operands)
{
    // Align to 4-byte boundary
    uint32 idx = reader.tellg();
    if(idx%4 != 0)
        idx += 4-idx%4;
    reader.seekg(idx);

    // Default
    Operand def(Operand::INT32, reader.read<int32>());
    operands.push_back(def);

    // Pairs
    int32 low = reader.read<int32>();
    operands.push_back(Operand(Operand::INT32, low));

    int32 high = reader.read<int32>();
    operands.push_back(Operand(Operand::INT32, high));

    for(int32 k=0; k<high-low+1; k++)
    {
        // Offset
        Operand offset(Operand::INT32, reader.read<int32>());
        operands.push_back(offset);
    }
}


Operand readOperand(StreamReader& reader, Operand::Type type)
{
    switch(type)
    {
        case Operand::INT8:
            return Operand(Operand::INT8, reader.read<int8>());

        case Operand::UINT8:
            return Operand(Operand::UINT8, reader.read<uint8>());

        case Operand::INT16:
            return Operand(Operand::INT16, reader.read<int16>());

        case Operand::UINT16:
            return Operand(Operand::UINT16, reader.read<uint16>());

        case Operand::INT32:
            return Operand(Operand::INT32, reader.read<int32>());

        case Operand::UINT32:
            return Operand(Operand::UINT32, reader.read<uint32>());

        default:
            return Operand();
    }
}


std::vector<Instruction> Decoder::decode(const std::vector<uint8>& bytes)
{
    StreamReader reader(bytes, StreamReader::BigEndian);
    std::vector<Instruction> instructions;

    // Decode instructions until end of stream
    while(!reader.eos())
    {
        Instruction instruction;
        instruction.offset = reader.tellg();

        // Get opcode "template"
        Opcode opcode = Opcode::table[reader.read<uint8>()];

        instruction.mnemonic = opcode.mnemonic;

        // Read operands
        if(instruction.mnemonic == LOOKUPSWITCH)
        {
            readLookupSwitch(reader, instruction.operands);
        }
        else if(instruction.mnemonic == TABLESWITCH)
        {
            readTableSwitch(reader, instruction.operands);
        }
        else if(instruction.mnemonic == WIDE)
        {
            Opcode opcode = Opcode::table[reader.read<uint8>()];

            instruction.mnemonic = opcode.mnemonic;

            if(instruction.mnemonic == IINC)
            {
                Operand index(Operand::UINT16, reader.read<uint16>());
                instruction.operands.push_back(index);

                Operand constant(Operand::INT16, reader.read<int16>());
                instruction.operands.push_back(constant);
            }
            else
            {
                Operand index(Operand::UINT16, reader.read<uint16>());
                instruction.operands.push_back(index);
            }
        }
        else
        {
            for(Operand::Type type: opcode.operands)
            {
                if(type == Operand::DUMMY)
                    reader.skip(1);
                else
                    instruction.operands.push_back(readOperand(reader, type));
            }
        }

        // Save instruction
        instructions.push_back(instruction);
    }

    return instructions;
}

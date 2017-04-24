#include "attribute-reader.hpp"

#include "../utils.hpp"


void AttributeReader::readAttributes(StreamReader& reader, const ConstantPool& pool)
{
    uint16 attributesCount = reader.read<uint16>();

    for(uint16 k=0; k<attributesCount; k++)
    {
        uint16 nameIndex = reader.read<uint16>();
        uint32 length = reader.read<uint32>();

        if(pool.string(nameIndex) == "ConstantValue")
        {
            readConstantValue(reader, pool);
        }
        else if(pool.string(nameIndex) == "Code")
        {
            readCode(reader, pool);
        }
        else // Unknown attribute
        {
            reader.skip(length);
        }
    }
}


std::shared_ptr<Attribute> AttributeReader::get(const std::string& name)
{
    auto it = m_attributes.find(name);

    if(it == m_attributes.end())
        return nullptr;

    return it->second;
}


void AttributeReader::readConstantValue(StreamReader& reader, const ConstantPool& pool)
{
    std::shared_ptr<Attribute> attribute(new ConstantValue());
    ConstantValue* a = dynamic_cast<ConstantValue*>(attribute.get());

    uint16 idx = reader.read<uint16>();

    switch(pool[idx].type())
    {
        case ConstantPoolEntry::Integer:
        case ConstantPoolEntry::Long:
            a->isSet = true;
            a->intValue = pool[idx].data();
            break;

        case ConstantPoolEntry::Float:
            a->isSet = true;
            a->doubleValue = bytesToFloat(pool[idx].data());
            break;

        case ConstantPoolEntry::Double:
            a->isSet = true;
            a->doubleValue = bytesToDouble(pool[idx].data());
            break;

        case ConstantPoolEntry::String:
            a->isSet = true;
            a->stringValue = pool.string(pool[idx].index1());
            break;

        default:
            throw AttributeError("Invalid constant value");
    }

    m_attributes["ConstantValue"] = attribute;
}


void AttributeReader::readCode(StreamReader& reader, const ConstantPool& pool)
{
    std::shared_ptr<Attribute> attribute(new Code());
    Code* a = dynamic_cast<Code*>(attribute.get());

    /*uint16 maxStack =*/ reader.read<uint16>();
    /*uint16 maxLocal =*/ reader.read<uint16>();

    // Code
    uint32 codeLength = reader.read<uint32>();
    for(uint32 k=0; k<codeLength; k++)
        a->code.push_back(reader.read<uint8>());

    // Exceptions
    uint16 exceptionLength = reader.read<uint16>();
    for(uint32 k=0; k<exceptionLength; k++)
    {
        Code::Exception exception;
        exception.start = reader.read<uint16>();
        exception.end = reader.read<uint16>();
        exception.handler = reader.read<uint16>();
        uint16 idx = reader.read<uint16>();
        exception.type = pool.string(pool[idx].index1());
        a->exceptions.push_back(exception);
    }

    // Attributes
    AttributeReader ar;
    ar.readAttributes(reader, pool);

    m_attributes["Code"] = attribute;
}

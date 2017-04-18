#include "attribute.hpp"

#include <algorithm>


void ConstantValue::read(StreamReader& reader, const ConstantPool& cp)
{
    uint16 idx = reader.read<uint16>();

    switch(cp[idx].type())
    {
        case ConstantPoolEntry::Integer:
        case ConstantPoolEntry::Long:
            isSet = true;
            intValue = cp[idx].data();
            break;

        case ConstantPoolEntry::Float:
        {
            isSet = true;
            uint32 f = (uint32)cp[idx].data();
            doubleValue = *reinterpret_cast<float*>(&f);
            break;
        }

        case ConstantPoolEntry::Double:
        {
            isSet = true;
            uint64 d = cp[idx].data();
            doubleValue = *reinterpret_cast<double*>(&d);
            break;
        }

        case ConstantPoolEntry::String:
            isSet = true;
            stringValue = cp.string(cp[idx].index1());
            break;

        default:
            throw AttributeError("Invalid constant value");
    }
}


bool operator==(const ConstantValue& cv1, const ConstantValue& cv2)
{
    return (cv1.type == cv2.type) &&
            (cv1.isSet == cv2.isSet) &&
            (cv1.intValue == cv2.intValue) &&
            (cv1.doubleValue == cv2.doubleValue) &&
            (cv1.stringValue == cv2.stringValue);
}


bool operator!=(const ConstantValue& cv1, const ConstantValue& cv2)
{
    return !(cv1==cv2);
}



void Code::read(StreamReader& reader, const ConstantPool& cp)
{
    /*uint16 maxStack =*/ reader.read<uint16>();
    /*uint16 maxLocal =*/ reader.read<uint16>();

    // Code
    uint32 codeLength = reader.read<uint32>();
    for(uint32 k=0; k<codeLength; k++)
        code.push_back(reader.read<uint8>());

    // Exceptions
    uint16 exceptionLength = reader.read<uint16>();
    for(uint32 k=0; k<exceptionLength; k++)
    {
        Exception exception;
        exception.start = reader.read<uint16>();
        exception.end = reader.read<uint16>();
        exception.handler = reader.read<uint16>();
        uint16 idx = reader.read<uint16>();
        exception.type = cp.string(cp[idx].index1());
        exceptions.push_back(exception);
    }

    // Attributes
    uint16 attributesCount = reader.read<uint16>();
    for(uint16 k=0; k<attributesCount; k++)
    {
        /*uint16 nameIndex =*/ reader.read<uint16>();
        uint32 length = reader.read<uint32>();
        reader.skip(length);
    }
}


bool operator==(const Code& code1, const Code& code2)
{
    return (code1.code.size() == code2.code.size()) &&
            (std::equal(code1.code.begin(), code1.code.end(), code2.code.begin())) &&
            (code1.exceptions.size() == code2.exceptions.size()) &&
            (std::equal(code1.exceptions.begin(), code1.exceptions.end(), code2.exceptions.begin())) &&
            (code1.type == code2.type) &&
            (code1.isSet == code2.isSet);
}


bool operator!=(const Code& code1, const Code& code2)
{
    return !(code1==code2);
}


bool operator==(const Code::Exception& code1, const Code::Exception& code2)
{
    return (code1.start == code2.start) &&
            (code1.end == code2.end) &&
            (code1.handler == code2.handler) &&
            (code1.type == code2.type);
}


bool operator!=(const Code::Exception& code1, const Code::Exception& code2)
{
    return !(code1 == code2);
}

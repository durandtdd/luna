#include "attribute.hpp"


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

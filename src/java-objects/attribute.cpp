#include "attribute.hpp"

#include <algorithm>


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

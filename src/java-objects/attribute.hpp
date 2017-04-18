#pragma once

#include <string>
#include <vector>

#include "../common.hpp"
#include "../constant-pool.hpp"
#include "../streamreader.hpp"


/**
 * @brief Error thrown by attributes
 */
class AttributeError: public Error
{
    using Error::Error;
};


/**
 * @brief Base abstract class for all attributes
 */
struct Attribute
{
    /**
     * @brief Supported attributes
     */
    enum Type
    {
        ConstantValue,
        Unknown
    };

    /** Type */
    Type type = Unknown;

    /** Flag indicating that the attribute is set in the file */
    bool isSet = false;


    /**
     * @brief Read the attribute from the stream
     * @param reader Stream reader
     * @param cp Constant pool
     */
    virtual void read(StreamReader& reader, const ConstantPool& cp) = 0;
};



/**
 * @brief A ContantValue
 */
struct ConstantValue: public Attribute
{
    /** Integer value (only for int types) */
    std::int64_t intValue = 0;

    /** Double value (only for float types) */
    double doubleValue = 0;

    /** String value (only for string types) */
    std::string stringValue;

    /**
     * @brief Construct a ConstantValue
     */
    ConstantValue() {type = Attribute::ConstantValue;}

    /**
     * @see Attribute::read
     */
    void read(StreamReader& reader, const ConstantPool& cp) override;
};


/**
 * @brief Compare two constant values
 * @param cv1 Constant value 1
 * @param cv2 Constant value 2
 * @return True if constant values are equal
 */
bool operator==(const ConstantValue& cv1, const ConstantValue& cv2);


/**
 * @brief Compare two constant values
 * @param cv1 Constant value 1
 * @param cv2 Constant value 2
 * @return True if constant values are different
 */
bool operator!=(const ConstantValue& cv1, const ConstantValue& cv2);

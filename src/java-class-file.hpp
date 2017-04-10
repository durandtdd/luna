#pragma once

#include <string>
#include <vector>

#include "common.hpp"

#include "constant-pool.hpp"
#include "java-objects/field.hpp"
#include "java-objects/method.hpp"


class StreamReader;


/**
 * @brief Error thrown if a file error occurs
 */
class FileError: public Error
{
public:
    using Error::Error;
};


/**
 * @brief Error thrown if a file error occurs
 */
class CorruptedFileError: public Error
{
public:
    using Error::Error;
};



/**
 * @brief Class representing a Java class file
 */
class JavaClassFile
{
public:
    /**
     * @brief Construct a JavaClassFile
     * @param name Filename
     * @throw Error Subclass thrown if an error occurs
     */
    JavaClassFile(const std::string& name);

    /**
     * @brief Decode the class file to a string
     * @return Decoded class file
     */
    std::string decode() const;


private:
    /**
     * @brief Read the class file header
     * @param reader Reader
     */
    void readHeader(StreamReader& reader);

    /**
     * @brief Read the constant pool
     * @param reader Reader
     */
    void readConstantPool(StreamReader& reader);

    /**
     * @brief Read the class direct interfaces
     * @param reader Reader
     */
    void readInterfaces(StreamReader& reader);

    /**
     * @brief Read the class fields
     * @param reader Reader
     */
    void readFields(StreamReader& reader);

    /**
     * @brief Read the class methods
     * @param reader Reader
     */
    void readMethods(StreamReader& reader);

    /**
     * @brief Read the attributes
     * @param reader Reader
     */
    void readAttributes(StreamReader& reader);


private:
    /** File bytes */
    std::vector<uint8> m_bytes;

    /** Constant pool */
    ConstantPool m_constantPool;

    /** Class name */
    std::string m_name;

    /** Super class name */
    std::string m_superName;

    /** Interfaces */
    std::vector<std::string> m_interfaces;

    /** Fields */
    std::vector<Field> m_fields;

    /** Methods */
    std::vector<Method> m_methods;
};

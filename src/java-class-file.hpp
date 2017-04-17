#pragma once

#include <string>
#include <vector>

#include "common.hpp"

#include "constant-pool.hpp"
#include "java-objects/class.hpp"


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


    Class javaClass() const;

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

    /** Class */
    Class m_class;
};

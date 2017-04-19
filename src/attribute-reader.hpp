#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "constant-pool.hpp"
#include "streamreader.hpp"
#include "java-objects/attribute.hpp"


/**
 * @brief Object reading a sequence of attributes in the stream
 */
class AttributeReader
{
public:
    /**
     * @brief Read next sequence of attributes
     * @param reader Reader
     * @param pool Constant pool
     */
    void readAttributes(StreamReader& reader, const ConstantPool& pool);

    /**
     * @brief Get the attribute from name
     * @param name Attribute name
     * @return Attribute or nullptr if no such attribute exists
     */
    std::shared_ptr<Attribute> get(const std::string& name);


private:
    /**
     * @brief Read a ConstantValue
     * @param reader Reader
     * @param pool Constant pool
     */
    void readConstantValue(StreamReader& reader, const ConstantPool& pool);

    /**
     * @brief Read a Code
     * @param reader Reader
     * @param pool Constant pool
     */
    void readCode(StreamReader& reader, const ConstantPool& pool);


private:
    /** Read attributes */
    std::unordered_map<std::string, std::shared_ptr<Attribute>> m_attributes;
};

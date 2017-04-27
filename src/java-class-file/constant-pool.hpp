#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../common.hpp"
#include "constant-pool-entry.hpp"
#include "java-object-ref.hpp"


/**
 * @brief Error thrown by ConstantPool class
 */
class ConstantPoolError: public Error
{
public:
    using Error::Error;
};


/**
 * @brief The constant pool of a class file
 *
 * This class manages the entries and Utf8 associated strings
 * Utf8 entries index1 must match and a string in the string table
 * addString can be used to add a string in the string table
 */
class ConstantPool
{
public:
    /**
     * @brief Add an entry to the pool
     * @param cpe Entry
     */
    void addEntry(const ConstantPoolEntry& cpe);

    /**
     * @brief Add a string
     * @param str String
     * @return Index of added string
     */
    uint16 addString(const std::string& str);

    /**
     * @brief Get entry
     * @param index Entry index
     * @return Entry
     * @throw ConstantPoolError If index is out of range
     */
    const ConstantPoolEntry& operator[](uint16 index) const;

    /**
     * @brief Get entry
     * @param index Entry index
     * @return Entry
     * @throw ConstantPoolError If index is out of range
     */
    ConstantPoolEntry& operator[](uint16 index);

    /**
     * @brief Return number of entries
     * @return Number of entries
     */
    std::size_t size() const;

    /**
     * @brief Get string at index (only Utf8 or String)
     * @param index Index
     * @return String
     * @throw ConstantPoolError If index is out of range or entry is not Utf8 or String
     */
    std::string getString(uint16 index) const;

    /**
     * @brief Get java object ref at index
     * @param index Index
     * @return Reference
     * @throw ConstantPoolError If index is out of range or entry is not a reference
     */
    std::shared_ptr<JavaObjectRef> getRef(uint16 index) const;

    /**
     * @brief Get int at index
     * @param index Index
     * @return Int value
     * @throw ConstantPoolError If index is out of range or entry is not a reference
     */
    int64 getInt(uint16 index) const;

    /**
     * @brief Get double at index
     * @param index Index
     * @return Int value
     * @throw ConstantPoolError If index is out of range or entry is not a reference
     */
    double getDouble(uint16 index) const;

    /**
     * @brief Convert constant pool to a string representation
     * @return String
     */
    std::string str() const;


private:
    /** Entries */
    std::vector<ConstantPoolEntry> m_entries;

    /** Strings */
    std::vector<std::string> m_strings;
};

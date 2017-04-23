#pragma once

#include <string>
#include <vector>

#include "../common.hpp"
#include "constant-pool-entry.hpp"


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
     */
    void addString(const std::string& str);

    /**
     * @brief Get string of entry (only Utf8)
     * @param index Index of entry
     * @return String
     * @throw ConstantPoolError If index is out of range or entry is not Utf8
     */
    std::string string(uint16 index) const;

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
     * @brief Return number of strings in the string table
     * @return Number of strings
     */
    std::size_t stringsSize() const;


private:
    /** Entries */
    std::vector<ConstantPoolEntry> m_entries;

    /** Strings */
    std::vector<std::string> m_strings;
};

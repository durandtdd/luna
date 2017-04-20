#include "constant-pool.hpp"

#include <sstream>


void ConstantPool::addEntry(const ConstantPoolEntry& cpe)
{
    m_entries.push_back(cpe);
}


void ConstantPool::addString(const std::string& str)
{
    m_strings.push_back(str);
}


std::string ConstantPool::string(uint16 index) const
{
    if(index >= m_entries.size())
        throw ConstantPoolError("Index out of range");

    if(m_entries[index].type() != ConstantPoolEntry::Utf8)
        throw ConstantPoolError("ConstantPoolEntry is not UTF8");

    if(m_entries[index].index1() >= m_strings.size())
        throw ConstantPoolError("Invalid string table index");

    return m_strings[m_entries[index].index1()];
}


const ConstantPoolEntry& ConstantPool::operator[](uint16 index) const
{
    if(index >= m_entries.size())
        throw ConstantPoolError("Index out of range");

    return m_entries[index];
}


ConstantPoolEntry& ConstantPool::operator[](uint16 index)
{
    if(index >= m_entries.size())
        throw ConstantPoolError("Index out of range");

    return m_entries[index];
}


size_t ConstantPool::size() const
{
    return m_entries.size();
}


size_t ConstantPool::stringsSize() const
{
    return m_strings.size();
}


std::string ConstantPool::str() const
{
    std::ostringstream oss;

    oss << "[\n";
    for(const auto& entry: m_entries)
        oss << "    " << entry.str() << "\n";
    oss << "]\n";

    return oss.str();
}

#include "streamreader.hpp"


StreamReader::StreamReader(const std::vector<uint8>& bytes):
    m_bytes(bytes),
    m_offset(0)
{
}


void StreamReader::seekg(uint32 offset)
{
    if(offset > m_bytes.size())
        throw EndOfStreamError("Not enough bytes");

    m_offset = offset;
}


void StreamReader::skip(uint32 nb)
{
    if(m_offset + nb > m_bytes.size())
        throw EndOfStreamError("Not enough bytes");

    m_offset += nb;
}


uint32 StreamReader::tellg() const
{
    return m_offset;
}


uint32 StreamReader::size() const
{
    return (uint32)m_bytes.size();
}


bool StreamReader::eos() const
{
    return m_offset >= m_bytes.size();
}

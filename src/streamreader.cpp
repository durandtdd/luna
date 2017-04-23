#include "streamreader.hpp"


StreamReader::StreamReader(const std::vector<uint8>& bytes, Endian endian):
    m_offset(0),
    m_endian(endian),
    m_bytes(bytes)
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

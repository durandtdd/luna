#pragma once

#include "common.hpp"

#include <vector>


/**
 * @brief Error thrown if (past) end of stream is reached
 */
class EndOfStreamError: public Error
{
public:
    using Error::Error;
};


/**
 * @brief Class used to read and interpret a byte stream
 */
class StreamReader
{
    public:
        /**
         * @brief Stream endianness
         */
        enum Endian
        {
            LittleEndian,
            BigEndian
        };


    public:
        /**
         * @brief Construct a StreamReader
         * @param bytes Bytes to read
         */
        StreamReader(const std::vector<uint8>& bytes, Endian endian = LittleEndian);

        /**
         * @brief Read next byte(s)
         * @param move Move index after reading
         * @return Read value
         * @except EndOfStreamError if not enough bytes
         */
        template<typename T>
        T read(bool move = true);

        /**
         * @brief Move index to offset
         * @param offset Offset
         * @except EndOfStreamError if offset is bigger than size
         */
        void seekg(uint32 offset);

        /**
         * @brief Skip the next bytes
         * @param nb Number of bytes
         * @except EndOfStreamError if not enough bytes
         */
        void skip(uint32 nb);

        /**
         * @brief Get offset
         * @return Offset
         */
        uint32 tellg() const;

        /**
         * @brief Get size
         * @return Size
         */
        uint32 size() const;

        /**
         * @brief Check if end of stream has been reached
         * @return True if end of stream
         */
        bool eos() const;


    private:
        /** Current offset in the byte stream */
        uint32 m_offset;

        /** Endianness */
        Endian m_endian;

        /** Bytes stream */
        const std::vector<uint8>& m_bytes;
};


template<typename T>
T StreamReader::read(bool move)
{
    uint32 sz = sizeof(T);

    if(m_offset + sz > m_bytes.size())
        throw EndOfStreamError("Not enough bytes");

    T value;

    // Read
    if(m_endian == LittleEndian)
        value = *reinterpret_cast<const T*>(m_bytes.data() + m_offset);
    else
    {
        std::vector<uint8> buffer(sz);
        for(uint32 k=0; k<buffer.size(); k++)
            buffer[sz-1-k] = m_bytes[m_offset+k];
        value = *reinterpret_cast<const T*>(buffer.data());
    }

    // Move index if needed
    if(move)
        m_offset += sz;

    return value;
}

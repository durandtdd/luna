#pragma once

#include <cstdint>
#include <exception>
#include <string>


// Typedefs
typedef std::uint8_t uint8;
typedef std::uint16_t uint16;
typedef std::uint32_t uint32;
typedef std::uint64_t uint64;
typedef std::int8_t int8;
typedef std::int16_t int16;
typedef std::int32_t int32;
typedef std::int64_t int64;


/**
 * @brief Base class for errors
 */
class Error: public std::exception
{
public:
    /**
     * @brief Construct an Error
     * @param message Error message
     */
    Error(const std::string& message): m_message(message) {}

    /**
     * @brief Get error message
     * @return Message
     */
    virtual const char* what() const noexcept override { return m_message.c_str();}

private:
    /** Error message */
    std::string m_message;
};

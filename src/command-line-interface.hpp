#pragma once

#include <string>

#include "common.hpp"
#include "java-class-file.hpp"
#include "java-objects/class.hpp"


/**
 * @brief Error thrown by the CommandLineInterface
 */
class CommandLineInterfaceError: public Error
{
    using Error::Error;
};


/**
 * @brief Object interfacing command line and code
 */
class CommandLineInterface
{
public:
    /**
     * @brief Construct a CommandLineInterface
     * @param filename File name
     */
    CommandLineInterface(const std::string& filename = "");

    /**
     * @brief Open a java file
     * @param filename File name
     */
    void open(const std::string& filename);

    /**
     * @brief Print the class name
     */
    void printName() const;

    /**
     * @brief Print the super clase
     */
    void printSuper() const;

    /**
     * @brief Print the interfaces
     */
    void printInterfaces() const;

    /**
     * @brief Print the fields
     */
    void printFields() const;

    /**
     * @brief Print the methods
     */
    void printMethods() const;

    /**
     * @brief Print constant pool
     */
    void printConstantPool() const;

    /**
     * @brief Print decoded class
     */
    void printDecoded() const;


private:
    /** Java class file */
    JavaClassFile m_file;

    /** Java class */
    Class m_class;
};

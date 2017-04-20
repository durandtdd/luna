#include "command-line-interface.hpp"

#include <iostream>


CommandLineInterface::CommandLineInterface(const std::string& filename)
{
    if(filename != "")
        open(filename);
}


void CommandLineInterface::open(const std::string& filename)
{
    m_file.open(filename);
    m_class = m_file.javaClass();
}

void CommandLineInterface::printName() const
{
    std::cout << "Name:\n";
    std::cout << "    " << m_class.name << "\n";
    std::cout << "\n";
}


void CommandLineInterface::printSuper() const
{
    std::cout << "Super:\n";
    std::cout << "    " << m_class.base << "\n";
    std::cout << "\n";
}


void CommandLineInterface::printInterfaces() const
{
    std::cout << "Interfaces:\n";
    for(const std::string& interface: m_class.interfaces)
        std::cout << "    " << interface << "\n";
    std::cout << "\n";
}


void CommandLineInterface::printFields() const
{
    std::cout << "Fields:\n";
    for(const Field& field: m_class.fields)
        std::cout << "    " << field.str() << "\n";
    std::cout << "\n";
}


void CommandLineInterface::printMethods() const
{
    std::cout << "Methods:\n";
    for(const Method& method: m_class.methods)
        std::cout << "    " << method.str() << "\n";
    std::cout << "\n";
}

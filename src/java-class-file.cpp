#include "java-class-file.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

#include "attribute-reader.hpp"
#include "decoder/decoder.hpp"
#include "descriptor-parser.hpp"
#include "streamreader.hpp"
#include "string-converter.hpp"


JavaClassFile::JavaClassFile(const std::string& name)
{
    if(name != "")
        open(name);
}


void JavaClassFile::open(const std::string& name)
{
    // Read file
    std::ifstream file(name, std::ios::in | std::ios::binary);
    if(!file.is_open())
        throw FileError("Can't open file: " + name);

    file.seekg(0, std::ios::end);
    m_bytes.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    m_bytes.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    // Interpret file
    StreamReader reader(m_bytes, StreamReader::BigEndian);

    readHeader(reader);

    readConstantPool(reader);

    m_class.flags = reader.read<uint16>(); // Access flags

    uint16 idxName = reader.read<uint16>();
    m_class.name = m_constantPool.string(m_constantPool[idxName].index1());

    uint16 idxSuperName = reader.read<uint16>();
    m_class.base = m_constantPool.string(m_constantPool[idxSuperName].index1());
    std::replace(m_class.base.begin(), m_class.base.end(), '/', '.');

    readInterfaces(reader);

    readFields(reader);

    readMethods(reader);
}


Class JavaClassFile::javaClass() const
{
    return m_class;
}


ConstantPool JavaClassFile::constantPool() const
{
    return m_constantPool;
}


std::string JavaClassFile::decode() const
{
    std::ostringstream oss;

    oss << "/* CONTANT POOL\n" << StringConverter::str(m_constantPool) << "*/\n";

    oss << StringConverter::str(m_class) << "\n";
    oss << "{\n";

    for(const Field& field: m_class.fields)
        oss << "    " << StringConverter::str(field) << ";\n";

    oss << "\n";

    for(const Method& method: m_class.methods)
    {
        oss << "\n";
        oss << "    " << StringConverter::str(method) << "\n";
        oss << "    " << "{\n";

        Decoder decoder;
        auto instructions = decoder.decode(method.code.code);
        for(const Instruction& instruction: instructions)
            oss << "        " << StringConverter::str(instruction) << "\n";
        oss << "    " << "}\n";
    }

    oss << "}\n";

    return oss.str();
}


void JavaClassFile::readHeader(StreamReader& reader)
{
    uint32 magic = reader.read<uint32>();
    if(magic != 0xcafebabe)
        throw FileError("Not a Java class file");

    reader.skip(2); // Version major
    reader.skip(2); // Version minor
}


void JavaClassFile::readConstantPool(StreamReader& reader)
{
    uint16 constantPoolCount = reader.read<uint16>();

    // Entries starts at 1
    m_constantPool.addEntry(ConstantPoolEntry(ConstantPoolEntry::Invalid));

    // Read all entries
    while(m_constantPool.size() < constantPoolCount)
    {
        // Read type
        uint8 tag = reader.read<uint8>();
        ConstantPoolEntry::Type type = ConstantPoolEntry::typeFromInt(tag);

        // Read entry
        ConstantPoolEntry cpe(type);
        switch(type)
        {
            case ConstantPoolEntry::Utf8:
            {
                // Length
                uint16 length = reader.read<uint16>();

                // Read bytes
                std::string str(length, 0x00);
                for(uint16 k=0; k<length; k++)
                    str[k] = reader.read<uint8>();

                // Add to string table
                m_constantPool.addString(str);

                // Set entry index to string table index
                cpe.setIndex1((uint16)m_constantPool.stringsSize()-1);
                break;
            }

            case ConstantPoolEntry::Integer:
            case ConstantPoolEntry::Float:
                cpe.setData(reader.read<uint32>());
                break;

            case ConstantPoolEntry::Long:
            case ConstantPoolEntry::Double:
                cpe.setData(reader.read<uint64>());
                break;

            case ConstantPoolEntry::Class:
            case ConstantPoolEntry::String:
            case ConstantPoolEntry::MethodType:
                cpe.setIndex1(reader.read<uint16>());
                break;

            case ConstantPoolEntry::FieldRef:
            case ConstantPoolEntry::MethodRef:
            case ConstantPoolEntry::InterfaceMethodRef:
            case ConstantPoolEntry::NameAndType:
            case ConstantPoolEntry::InvokeDynamic:
                cpe.setIndex1(reader.read<uint16>());
                cpe.setIndex2(reader.read<uint16>());
                break;

            case ConstantPoolEntry::MethodHandle:
                cpe.setIndex1(reader.read<uint8>());
                cpe.setIndex2(reader.read<uint16>());
                break;

            case ConstantPoolEntry::Invalid:
                throw FileError("Corrupted file (Invalid constant pool entry tag)");
        }

        // Save entry
        m_constantPool.addEntry(cpe);

        // A long or double takes two entries...
        if(cpe.type() == ConstantPoolEntry::Long || cpe.type() == ConstantPoolEntry::Double)
            m_constantPool.addEntry(ConstantPoolEntry(ConstantPoolEntry::Invalid));
    }
}


void JavaClassFile::readInterfaces(StreamReader& reader)
{
    uint16 interfacesCount = reader.read<uint16>();

    for(uint16 k=0; k<interfacesCount; k++)
    {
        uint16 idx = reader.read<uint16>(); // Class index
        std::string interface = m_constantPool.string(m_constantPool[idx].index1());
        std::replace(interface.begin(), interface.end(), '/', '.');
        m_class.interfaces.push_back(interface);
    }
}


void JavaClassFile::readFields(StreamReader& reader)
{
    uint16 fieldsCount = reader.read<uint16>();

    for(uint16 k=0; k<fieldsCount; k++)
    {
        Field field;

        // Flags
        field.flags = reader.read<uint16>();

        // Name
        uint16 nameIndex = reader.read<uint16>();
        field.name = m_constantPool.string(nameIndex);

        // Descriptor
        uint16 descriptorIndex = reader.read<uint16>();
        std::string desc = m_constantPool.string(descriptorIndex);
        auto it = desc.begin();
        field.type = parseDescriptor(it, desc.end());

        // Attributes
        AttributeReader ar;
        ar.readAttributes(reader, m_constantPool);

        auto ptr = ar.get("ConstantValue");
        if(ptr != nullptr)
            field.value = *dynamic_cast<ConstantValue*>(ptr.get());

        // Save field
        m_class.fields.push_back(field);
    }
}


void JavaClassFile::readMethods(StreamReader& reader)
{
    uint16 methodsCount = reader.read<uint16>();

    for(uint16 k=0; k<methodsCount; k++)
    {
        Method method;

        // Flags
        method.flags = reader.read<uint16>();

        // Name
        uint16 nameIndex = reader.read<uint16>();
        method.name = m_constantPool.string(nameIndex);

        // Descriptor
        uint16 descriptorIndex = reader.read<uint16>();
        std::string desc = m_constantPool.string(descriptorIndex);

        auto it = desc.begin();

        ++it; // '('
        while(*it != ')')
        {
            Type type = parseDescriptor(it, desc.end());
            Variable var {type, "param" + std::to_string(method.parameters.size())};
            method.parameters.push_back(var);
        }

        ++it; // ')'
        method.type = parseDescriptor(it, desc.end());

        // Attributes
        AttributeReader ar;
        ar.readAttributes(reader, m_constantPool);

        auto ptr = ar.get("Code");
        if(ptr != nullptr)
            method.code = *dynamic_cast<Code*>(ptr.get());

        // Save method
        m_class.methods.push_back(method);
    }
}

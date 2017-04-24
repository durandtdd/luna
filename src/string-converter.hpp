#pragma once

#include "decoder/instruction.hpp"
#include "java-class-file/constant-pool.hpp"
#include "java-objects/type.hpp"
#include "java-objects/variable.hpp"
#include "java-objects/field.hpp"
#include "java-objects/method.hpp"
#include "java-objects/class.hpp"


/**
 * @brief Class used to convert objects to string
 */
class StringConverter
{
public:
    /**
     * @brief Convert a type to a string
     * @param type Type
     * @return String
     */
    static std::string str(const Type& type);

    /**
     * @brief Convert a variable to a string
     * @param variable Variable
     * @return String
     */
    static std::string str(const Variable& variable);

    /**
     * @brief Convert a field to a string
     * @param field Field
     * @param allFlags True: print all flags, False: Print only non implicit flags (public, final...)
     * @return String
     */
    static std::string str(const Field& field, bool allFlags = false);

    /**
     * @brief Convert a method to a string
     * @param method Method
     * @param allFlags True: print all flags, False: Print only non implicit flags (public, final...)
     * @return String
     */
    static std::string str(const Method& method, bool allFlags = false);

    /**
     * @brief Convert a class to a string
     * @param class Class
     * @param allFlags True: print all flags, False: Print only non implicit flags (public, final...)
     * @return String
     */
    static std::string str(const Class& cl, bool allFlags = false);

    /**
     * @brief Convert a ConstantPool to a string
     * @param cp Constant pool
     * @return String
     */
    static std::string str(const ConstantPool& cp);

    /**
     * @brief Convert an instruction to a string
     * @param instruction Instruction
     * @return String
     */
    static std::string str(const Instruction& instruction);

    /**
     * @brief Convert a java object ref to a string
     * @param ref Reference
     * @return String
     */
    static std::string str(const JavaObjectRef& ref);
};

#include "catch/catch.hpp"

#include <algorithm>

#include "../src/java-class-file.hpp"


TEST_CASE("Java class fields and methods")
{
    //TODO Test field synthetic
    //TODO Test method synthetic bridge strict
    //TODO Test class synthetic annotation

    Class cl;
    std::vector<Field> fields;
    std::vector<Method> methods;

    // Compare partially fields (type, name, flags)
    auto isField = [&cl](const Field& field)
        {
            for(const Field& f: cl.fields)
                if((f.type == field.type) &&
                        (f.name == field.name) &&
                        (f.flags == field.flags))
                    return true;
            return false;
        };

    // Compare partially methods (type, flags, name, parameters)
    auto isMethod = [&cl](const Method& method)
        {
            for(const Method& m: cl.methods)
                if((m.type == method.type) &&
                        (m.name == method.name) &&
                        (m.flags == method.flags) &&
                        (m.parameters.size() == method.parameters.size()) &&
                        std::equal(m.parameters.begin(), m.parameters.end(), method.parameters.begin()))
                    return true;
            return false;
        };

    // Test
    cl = JavaClassFile("test/files/Test.class").javaClass();
    REQUIRE(cl.name == "Test");
    REQUIRE(cl.base == "java.lang.Object");
    REQUIRE(cl.flags == (Class::AccPublic | Class::AccSuper));

    {
    Field field;
    field.type = Type::tBoolean();
    field.name = "booleanField";
    field.flags = Field::AccPrivate;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tByte();
    field.name = "byteField";
    field.flags = Field::AccPrivate;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tChar();
    field.name = "charField";
    field.flags = Field::AccPrivate;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tDouble();
    field.name = "doubleField";
    field.flags = Field::AccPrivate;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tFloat();
    field.name = "floatField";
    field.flags = Field::AccPrivate;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tInt();
    field.name = "intField";
    field.flags = Field::AccPrivate;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tLong();
    field.name = "longField";
    field.flags = Field::AccPrivate;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tShort();
    field.name = "shortField";
    field.flags = Field::AccPrivate;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tObject("java.lang.String");
    field.name = "stringField";
    field.flags = Field::AccPrivate;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tInt(3);
    field.name = "intTripleArrayField";
    field.flags = Field::AccPrivate;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tInt();
    field.name = "finalField";
    field.flags = Field::AccPrivate | Field::AccFinal;
    field.value.isSet = true;
    field.value.intValue = 123;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tDouble();
    field.name = "finalDoubleField";
    field.flags = Field::AccPrivate | Field::AccFinal;
    field.value.isSet = true;
    field.value.doubleValue = 1.618;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tObject("java.lang.String");
    field.name = "finalStringField";
    field.flags = Field::AccPrivate | Field::AccFinal;
    field.value.isSet = true;
    field.value.stringValue = "Hello, world";
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tInt();
    field.name = "staticField";
    field.flags = Field::AccPrivate | Field::AccStatic;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tInt();
    field.name = "volatileField";
    field.flags = Field::AccPrivate | Field::AccVolatile;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tInt();
    field.name = "transientField";
    field.flags = Field::AccPrivate | Field::AccTransient;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tInt();
    field.name = "publicField";
    field.flags = Field::AccPublic;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tInt();
    field.name = "packageField";
    field.flags = 0;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tInt();
    field.name = "protectedField";
    field.flags = Field::AccProtected;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tInt();
    field.name = "privateField";
    field.flags = Field::AccPrivate;
    REQUIRE(isField(field));
    }

    {
    Field field;
    field.type = Type::tObject("Test$Enum");
    field.name = "enumField";
    field.flags = Field::AccPrivate;
    REQUIRE(isField(field));
    }

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "publicMethod";
    method.parameters = {};
    method.flags = Method::AccPublic;
    REQUIRE(isMethod(method));
    }

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "packageMethod";
    method.parameters = {};
    method.flags = 0;
    REQUIRE(isMethod(method));
    }

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "protectedMethod";
    method.parameters = {};
    method.flags = Method::AccProtected;
    REQUIRE(isMethod(method));
    }

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "privateMethod";
    method.parameters = {};
    method.flags = Method::AccPrivate;
    REQUIRE(isMethod(method));
    }

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "staticMethod";
    method.parameters = {};
    method.flags = Method::AccPublic | Method::AccStatic;
    REQUIRE(isMethod(method));
    }

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "finalMethod";
    method.parameters = {};
    method.flags = Method::AccPublic | Method::AccFinal;
    REQUIRE(isMethod(method));
    }

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "synchronizedMethod";
    method.parameters = {};
    method.flags = Method::AccPublic | Method::AccSynchronized;
    REQUIRE(isMethod(method));
    }

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "varargsMethod";
    method.parameters = {{{Type::Object, "java.lang.Object", 1}, "param0"}};
    method.flags = Method::AccPublic | Method::AccVarArgs;
    REQUIRE(isMethod(method));
    }

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "nativeMethod";
    method.parameters = {};
    method.flags = Method::AccPublic | Method::AccNative;
    REQUIRE(isMethod(method));
    }

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "setIntMethod";
    method.parameters = {{Type::tInt(), "param0"}};
    method.flags = Method::AccPublic;
    REQUIRE(isMethod(method));
    }

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "setStringMethod";
    method.parameters = {{Type::tObject("java.lang.String", 0), "param0"}};
    method.flags = Method::AccPublic;
    REQUIRE(isMethod(method));
    }

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "setArrayMethod";
    method.parameters = {{Type::tObject("java.lang.String", 1), "param0"}};
    method.flags = Method::AccPublic;
    REQUIRE(isMethod(method));
    }

    {
    Method method;
    method.type = Type::tInt();
    method.name = "getIntMethod";
    method.parameters = {};
    method.flags = Method::AccPublic;
    REQUIRE(isMethod(method));
    }

    {
    Method method;
    method.type = Type::tObject("java.lang.String");
    method.name = "getStringMethod";
    method.parameters = {};
    method.flags = Method::AccPublic;
    REQUIRE(isMethod(method));
    }

    {
    Method method;
    method.type = Type::tInt();
    method.name = "doSomething";
    method.parameters = {{Type::tObject("java.lang.String", 1), "param0"}, {Type::tInt(), "param1"}, {Type::tFloat(), "param2"}};
    method.flags = Method::AccPublic;
    REQUIRE(isMethod(method));
    }


    // AbstractClass
    cl = JavaClassFile("test/files/Test$AbstractClass.class").javaClass();
    REQUIRE(cl.name == "Test$AbstractClass");
    REQUIRE(cl.base == "java.lang.Object");
    REQUIRE(cl.flags == (Class::AccAbstract | Class::AccSuper));

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "abstractMethod";
    method.parameters = {};
    method.flags = Method::AccPublic | Method::AccAbstract;
    REQUIRE(isMethod(method));
    }


    // Enum
    cl = JavaClassFile("test/files/Test$Enum.class").javaClass();
    REQUIRE(cl.name == "Test$Enum");
    REQUIRE(cl.base == "java.lang.Enum");
    REQUIRE(cl.flags == (Class::AccPublic | Class::AccFinal | Class::AccSuper | Class::AccEnum));

    {
    Field field;
    field.type = Type::tObject("Test$Enum");
    field.name = "EnumElement";
    field.flags = Field::AccPublic | Field::AccStatic | Field::AccFinal | Field::AccEnum;
    REQUIRE(isField(field));
    }


    // Interface
    cl = JavaClassFile("test/files/Test$Interface.class").javaClass();
    REQUIRE(cl.name == "Test$Interface");
    REQUIRE(cl.base == "java.lang.Object");
    REQUIRE(cl.flags == (Class::AccInterface | Class::AccAbstract));

    {
    Field field;
    field.type = Type::tInt();
    field.name = "interfaceField";
    field.flags = Field::AccPublic | Field::AccStatic | Field::AccFinal;
    field.value.isSet = true;
    field.value.intValue = 42;
    REQUIRE(isField(field));
    }

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "interfaceMethod";
    method.parameters = {};
    method.flags = Method::AccPublic | Method::AccAbstract;
    REQUIRE(isMethod(method));
    }


    // Final class
    cl = JavaClassFile("test/files/Test$FinalClass.class").javaClass();
    REQUIRE(cl.name == "Test$FinalClass");
    REQUIRE(cl.base == "Test$AbstractClass");
    REQUIRE(cl.flags == (Class::AccSuper | Class::AccFinal));
    REQUIRE(cl.interfaces[0] == "Test$Interface");

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "interfaceMethod";
    method.parameters = {};
    method.flags = Method::AccPublic;
    REQUIRE(isMethod(method));
    }

    {
    Method method;
    method.type = Type::tVoid();
    method.name = "abstractMethod";
    method.parameters = {};
    method.flags = Method::AccPublic;
    REQUIRE(isMethod(method));
    }
}


TEST_CASE("Java methods code")
{
    Class cl;
    std::vector<Method>::iterator method;

    cl = JavaClassFile("test/files/TestCode.class").javaClass();

    method = std::find_if(cl.methods.begin(), cl.methods.end(), [](const auto& m) {return m.name == "empty";});
    REQUIRE(method != cl.methods.end());
    REQUIRE(method->code.code.size() == 1);
    REQUIRE(method->code.code[0] == 0xb1);

    method = std::find_if(cl.methods.begin(), cl.methods.end(), [](const Method& m) {return m.name == "getInt";});
    REQUIRE(method != cl.methods.end());
    REQUIRE(method->code.code.size() == 2);
    REQUIRE(method->code.code[0] == 0x04);
    REQUIRE(method->code.code[1] == 0xac);

    method = std::find_if(cl.methods.begin(), cl.methods.end(), [](const Method& m) {return m.name == "getDouble";});
    REQUIRE(method != cl.methods.end());
    REQUIRE(method->code.code.size() == 4);
    REQUIRE(method->code.code[0] == 0x14);
    REQUIRE(method->code.code[3] == 0xaf);
}

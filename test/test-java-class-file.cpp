#include "catch/catch.hpp"

#include <algorithm>

#include "../src/java-class-file.hpp"


template<typename T>
void assertAllIn(const std::vector<T>& elements, const std::vector<T>& all)
{
    for(const T& element: elements)
    {
        bool isIn = std::any_of(all.begin(), all.end(), [element](T e){return e == element;});
        REQUIRE(isIn);
    }
}
#include <iostream>

TEST_CASE("Java class fields and methods")
{
    //TODO Test field synthetic
    //TODO Test method synthetic bridge strict
    //TODO Test class synthetic annotation

    Class cl;
    std::vector<Field> fields;
    std::vector<Method> methods;

    auto isField = [&cl](const Field& field) {return std::find(cl.fields.begin(), cl.fields.end(), field) != cl.fields.end();};
    auto isMethod = [&cl](const Method& method) {return std::find(cl.methods.begin(), cl.methods.end(), method) != cl.methods.end();};

    // Test
    cl = JavaClassFile("test/files/Test.class").javaClass();
    REQUIRE(cl.name == "Test");
    REQUIRE(cl.base == "java.lang.Object");
    REQUIRE(cl.flags == (Class::AccPublic | Class::AccSuper));

    REQUIRE(isField({Type::tBoolean(), "booleanField", Field::AccPrivate}));
    REQUIRE(isField({Type::tByte(), "byteField", Field::AccPrivate}));
    REQUIRE(isField({Type::tChar(), "charField", Field::AccPrivate}));
    REQUIRE(isField({Type::tDouble(), "doubleField", Field::AccPrivate}));
    REQUIRE(isField({Type::tFloat(), "floatField", Field::AccPrivate}));
    REQUIRE(isField({Type::tInt(), "intField", Field::AccPrivate}));
    REQUIRE(isField({Type::tLong(), "longField", Field::AccPrivate}));
    REQUIRE(isField({Type::tShort(), "shortField", Field::AccPrivate}));
    REQUIRE(isField({Type::tObject("java.lang.String"), "stringField", Field::AccPrivate}));
    REQUIRE(isField({Type::tInt(3), "intTripleArrayField", Field::AccPrivate}));
    REQUIRE(isField({Type::tObject("java.lang.String", 1), "stringArrayField", Field::AccPrivate}));
    REQUIRE(isField({Type::tInt(), "finalField", Field::AccPrivate | Field::AccFinal}));
    REQUIRE(isField({Type::tInt(), "staticField", Field::AccPrivate | Field::AccStatic}));
    REQUIRE(isField({Type::tInt(), "volatileField", Field::AccPrivate | Field::AccVolatile}));
    REQUIRE(isField({Type::tInt(), "transientField", Field::AccPrivate | Field::AccTransient}));
    REQUIRE(isField({Type::tInt(), "publicField", Field::AccPublic}));
    REQUIRE(isField({Type::tInt(), "packageField", 0}));
    REQUIRE(isField({Type::tInt(), "protectedField", Field::AccProtected}));
    REQUIRE(isField({Type::tInt(), "privateField", Field::AccPrivate}));
    REQUIRE(isField({Type::tObject("Test$Enum"), "enumField", Field::AccPrivate}));

    REQUIRE(isMethod({Type::tVoid(), "publicMethod", {}, Method::AccPublic}));
    REQUIRE(isMethod({Type::tVoid(), "packageMethod", {}, 0}));
    REQUIRE(isMethod({Type::tVoid(), "protectedMethod", {}, Method::AccProtected}));
    REQUIRE(isMethod({Type::tVoid(), "privateMethod", {}, Method::AccPrivate}));
    REQUIRE(isMethod({Type::tVoid(), "staticMethod", {}, Method::AccPublic | Method::AccStatic}));
    REQUIRE(isMethod({Type::tVoid(), "finalMethod", {}, Method::AccPublic | Method::AccFinal}));
    REQUIRE(isMethod({Type::tVoid(), "synchronizedMethod", {}, Method::AccPublic | Method::AccSynchronized}));
    REQUIRE(isMethod({Type::tVoid(), "varargsMethod", {{{Type::Object, "java.lang.Object", 1}, "param0"}}, Method::AccPublic | Method::AccVarArgs}));
    REQUIRE(isMethod({Type::tVoid(), "nativeMethod", {}, Method::AccPublic | Method::AccNative}));
    REQUIRE(isMethod({Type::tVoid(), "setIntMethod", {{Type::tInt(), "param0"}}, Method::AccPublic}));
    REQUIRE(isMethod({Type::tVoid(), "setStringMethod", {{Type::tObject("java.lang.String", 0), "param0"}}, Method::AccPublic}));
    REQUIRE(isMethod({Type::tVoid(), "setArrayMethod", {{Type::tObject("java.lang.String", 1), "param0"}}, Method::AccPublic}));
    REQUIRE(isMethod({Type::tInt(), "getIntMethod", {}, Method::AccPublic}));
    REQUIRE(isMethod({Type::tObject("java.lang.String"), "getStringMethod", {}, Method::AccPublic}));
    REQUIRE(isMethod({Type::tObject("java.lang.String", 1), "getArrayMethod", {}, Method::AccPublic}));
    REQUIRE(isMethod({Type::tInt(), "doSomething", {{Type::tObject("java.lang.String", 1), "param0"}, {Type::tInt(), "param1"}, {Type::tFloat(), "param2"}}, Method::AccPublic}));


    // AbstractClass
    cl = JavaClassFile("test/files/Test$AbstractClass.class").javaClass();
    REQUIRE(cl.name == "Test$AbstractClass");
    REQUIRE(cl.base == "java.lang.Object");
    REQUIRE(cl.flags == (Class::AccAbstract | Class::AccSuper));

    REQUIRE(isMethod({Type::tVoid(), "abstractMethod", {}, Method::AccPublic | Method::AccAbstract}));


    // Enum
    cl = JavaClassFile("test/files/Test$Enum.class").javaClass();
    REQUIRE(cl.name == "Test$Enum");
    REQUIRE(cl.base == "java.lang.Enum");
    REQUIRE(cl.flags == (Class::AccPublic | Class::AccFinal | Class::AccSuper | Class::AccEnum));

    REQUIRE(isField({Type::tObject("Test$Enum"), "EnumElement", Field::AccPublic | Field::AccStatic | Field::AccFinal | Field::AccEnum}));


    // Interface
    cl = JavaClassFile("test/files/Test$Interface.class").javaClass();
    REQUIRE(cl.name == "Test$Interface");
    REQUIRE(cl.base == "java.lang.Object");
    REQUIRE(cl.flags == (Class::AccInterface | Class::AccAbstract));

    REQUIRE(isField({Type::tInt(), "interfaceField", Field::AccPublic | Field::AccStatic | Field::AccFinal}));

    REQUIRE(isMethod({Type::tVoid(), "interfaceMethod", {}, Method::AccPublic | Method::AccAbstract}));


    // Final class
    cl = JavaClassFile("test/files/Test$FinalClass.class").javaClass();
    REQUIRE(cl.name == "Test$FinalClass");
    REQUIRE(cl.base == "Test$AbstractClass");
    REQUIRE(cl.flags == (Class::AccSuper | Class::AccFinal));
    REQUIRE(cl.interfaces[0] == "Test$Interface");

    REQUIRE(isMethod({Type::tVoid(), "interfaceMethod", {}, Method::AccPublic}));
    REQUIRE(isMethod({Type::tVoid(), "abstractMethod", {}, Method::AccPublic}));
}

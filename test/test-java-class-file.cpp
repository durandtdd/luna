#include "test.hpp"

#include <algorithm>
#include <initializer_list>
#include "../src/java-class-file.hpp"


template<typename T>
void assertAllIn(const std::vector<T>& elements, const std::vector<T>& all)
{
    for(const T& element: elements)
    {
        bool isIn = std::any_of(all.begin(), all.end(), [element](T e){return e == element;});
        ASSERT_TRUE_MSG(isIn, element.str());
    }
}


void testJavaClassFile()
{
    //TODO Test field synthetic
    //TODO Test method synthetic bridge strict
    //TODO Test class synthetic annotation

    Class cl;
    std::vector<Field> fields;
    std::vector<Method> methods;

    // Test
    cl = JavaClassFile("test/files/Test.class").javaClass();
    ASSERT_EQUAL(cl.name, "Test");
    ASSERT_EQUAL(cl.base, "java.lang.Object");
    ASSERT_EQUAL(cl.flags, Class::AccPublic | Class::AccSuper);

    fields =
    {
        {Type::tBoolean(), "booleanField", Field::AccPrivate},
        {Type::tByte(), "byteField", Field::AccPrivate},
        {Type::tChar(), "charField", Field::AccPrivate},
        {Type::tDouble(), "doubleField", Field::AccPrivate},
        {Type::tFloat(), "floatField", Field::AccPrivate},
        {Type::tInt(), "intField", Field::AccPrivate},
        {Type::tLong(), "longField", Field::AccPrivate},
        {Type::tShort(), "shortField", Field::AccPrivate},
        {Type::tObject("java.lang.String"), "stringField", Field::AccPrivate},
        {Type::tInt(3), "intTripleArrayField", Field::AccPrivate},
        {Type::tObject("java.lang.String", 1), "stringArrayField", Field::AccPrivate},
        {Type::tInt(), "finalField", Field::AccPrivate | Field::AccFinal},
        {Type::tInt(), "staticField", Field::AccPrivate | Field::AccStatic},
        {Type::tInt(), "volatileField", Field::AccPrivate | Field::AccVolatile},
        {Type::tInt(), "transientField", Field::AccPrivate | Field::AccTransient},
        {Type::tInt(), "publicField", Field::AccPublic},
        {Type::tInt(), "packageField", 0},
        {Type::tInt(), "protectedField", Field::AccProtected},
        {Type::tInt(), "privateField", Field::AccPrivate},
        {Type::tObject("Test$Enum"), "enumField", Field::AccPrivate},
    };

    assertAllIn(fields, cl.fields);

    methods =
    {
        {Type::tVoid(), "publicMethod", {}, Method::AccPublic},
        {Type::tVoid(), "packageMethod", {}, 0},
        {Type::tVoid(), "protectedMethod", {}, Method::AccProtected},
        {Type::tVoid(), "privateMethod", {}, Method::AccPrivate},
        {Type::tVoid(), "staticMethod", {}, Method::AccPublic | Method::AccStatic},
        {Type::tVoid(), "finalMethod", {}, Method::AccPublic | Method::AccFinal},
        {Type::tVoid(), "synchronizedMethod", {}, Method::AccPublic | Method::AccSynchronized},
        {Type::tVoid(), "varargsMethod", {{{Type::Object, "java.lang.Object", 1}, "param0"}}, Method::AccPublic | Method::AccVarArgs},
        {Type::tVoid(), "nativeMethod", {}, Method::AccPublic | Method::AccNative},
        {Type::tVoid(), "setIntMethod", {{Type::tInt(), "param0"}}, Method::AccPublic},
        {Type::tVoid(), "setStringMethod", {{Type::tObject("java.lang.String", 0), "param0"}}, Method::AccPublic},
        {Type::tVoid(), "setArrayMethod", {{Type::tObject("java.lang.String", 1), "param0"}}, Method::AccPublic},
        {Type::tInt(), "getIntMethod", {}, Method::AccPublic},
        {Type::tObject("java.lang.String"), "getStringMethod", {}, Method::AccPublic},
        {Type::tObject("java.lang.String", 1), "getArrayMethod", {}, Method::AccPublic},
        {Type::tInt(), "doSomething", {{Type::tObject("java.lang.String", 1), "param0"}, {Type::tInt(), "param1"}, {Type::tFloat(), "param2"}}, Method::AccPublic},
    };

    assertAllIn(methods, cl.methods);


    // AbstractClass
    cl = JavaClassFile("test/files/Test$AbstractClass.class").javaClass();
    ASSERT_EQUAL(cl.name, "Test$AbstractClass");
    ASSERT_EQUAL(cl.base, "java.lang.Object");
    ASSERT_EQUAL(cl.flags, Class::AccAbstract | Class::AccSuper);

    methods =
    {
        {Type::tVoid(), "abstractMethod", {}, Method::AccPublic | Method::AccAbstract},
    };

    assertAllIn(methods, cl.methods);


    // Enum
    cl = JavaClassFile("test/files/Test$Enum.class").javaClass();
    ASSERT_EQUAL(cl.name, "Test$Enum");
    ASSERT_EQUAL(cl.base, "java.lang.Enum");
    ASSERT_EQUAL(cl.flags, Class::AccPublic | Class::AccFinal | Class::AccSuper | Class::AccEnum);

    fields =
    {
        {Type::tObject("Test$Enum"), "EnumElement", Field::AccPublic | Field::AccStatic | Field::AccFinal | Field::AccEnum},
    };

    assertAllIn(fields, cl.fields);


    // Interface
    cl = JavaClassFile("test/files/Test$Interface.class").javaClass();
    ASSERT_EQUAL(cl.name, "Test$Interface");
    ASSERT_EQUAL(cl.base, "java.lang.Object");
    ASSERT_EQUAL(cl.flags, Class::AccInterface | Class::AccAbstract);

    fields =
    {
        {Type::tInt(), "interfaceField", Field::AccPublic | Field::AccStatic | Field::AccFinal},
    };

    assertAllIn(fields, cl.fields);


    methods =
    {
        {Type::tVoid(), "interfaceMethod", {}, Method::AccPublic | Method::AccAbstract},
    };

    assertAllIn(methods, cl.methods);


    // Interface
    cl = JavaClassFile("test/files/Test$FinalClass.class").javaClass();
    ASSERT_EQUAL(cl.name, "Test$FinalClass");
    ASSERT_EQUAL(cl.base, "Test$AbstractClass");
    ASSERT_EQUAL(cl.flags, Class::AccPublic | Class::AccFinal);
    ASSERT_EQUAL(cl.interfaces[0], "Test$Interface");

    methods =
    {
        {Type::tVoid(), "interfaceMethod", {}, Method::AccPublic},
        {Type::tVoid(), "abstractMethod", {}, Method::AccPublic},
    };

    assertAllIn(methods, cl.methods);
}

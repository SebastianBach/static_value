#include "static_value.h"

namespace internaltypes
{
struct myID;
struct myValue;
}

using MyID = StaticValue<unsigned int, internaltypes::myID>;
using MyValue = StaticValue<unsigned int, internaltypes::myValue>;


void IllegalCode()
{
    // It must not be possible to compile this code

#ifdef COMPILE_BAD_CODE

    // no assignment from POD; implicit construction
    {
        MyID myID = 123;
    }

    // no comparison with POD
    {
        MyID myID { 123 };
        auto res = myID == 123;
    }

    // no assignment from other type
    {
        MyID myID { 123 };
        MyValue myValue { 456 };
        myID = myValue;
    }

    // no comparison with other type
    {
        MyID myID { 123 };
        MyValue myValue { 456 };
        auto res = myID == myValue;
    }

    // no arithmetic operations
    {
        MyID idA { 123 };
        MyID idB { 123 };
        auto res = idA + idB;
    }
#endif
}

#include<iostream>

void CorrectUse()
{
    MyID firstID { 123 };
    MyID secondID { 456 };

    // compare

    const auto res = firstID != secondID;
    if (res)
    {
        std::cout << "IDs are the same" << std::endl;
    }

    // assign new value

    MyID thirdID { 0 };
    thirdID = MyID { 789 };

    std::cout << "ID: " << thirdID.GetValue() << std::endl;
}

void CompileTimeUnitTest()
{
    constexpr MyID::DataType value = 123;

    constexpr MyID idA { value };

    // test value

    constexpr auto gotValue = idA.GetValue();
    constexpr auto testValue = gotValue == value;
    static_assert(testValue, "StaticValue::GetValue() Failure");

    // test equality/inequality

    constexpr MyID idB { value };
    constexpr auto testEquality = idA == idB;

    static_assert(testEquality, "StaticValue Equality Failure");

    constexpr MyID idC { 456 };
    constexpr auto testInequality = idA != idC;

    static_assert(testInequality, "StaticValue Inequality Failure");
}


int main()
{
    IllegalCode();
    CorrectUse();
    CompileTimeUnitTest();

    return 0;
}
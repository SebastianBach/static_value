#ifndef STATIC_VALUE_H__
#define STATIC_VALUE_H__

#include <type_traits>

//-----------------------------------------------------------------------------
// A class template as a base class for specific ID types.
// Such ID types represent values that can only be compared for equality/inequality.
// No further operations are allowed.
//
// See Arno Lepisk: "Avoiding Disasters with Strongly Typed C++" 
// https://www.youtube.com/watch?v=1fwbG5TyI18
//
// T defines the data type used to represent the actual ID.
// X defines a unique type.
// Y optional third type.
//-----------------------------------------------------------------------------
template <typename T, typename X, typename Y = void>
struct StaticValue
{
    static_assert(std::is_integral<T>::value || std::is_enum<T>::value, "Use StaticValue only with POD.");

    // The type itself.
    using Type = StaticValue<T, X, Y>;

    // The data type of the ID.
    // Can be used to create a variable with the data type.
    // 
    // const MyID::DataType v = myId.GetValue();
    using DataType = T;

    //-----------------------------------------------------------------------------
    // Explicit constructor to avoid unintended construction.
    //
    // @param[in] v		The value to store.
    //-----------------------------------------------------------------------------
    explicit constexpr StaticValue(DataType v) : _value(v) { }

    //-----------------------------------------------------------------------------
    // Returns the stored value. E.g. to store it in a file.
    //
    // @return 	The stored value.
    //-----------------------------------------------------------------------------
    constexpr DataType GetValue() const
    {
        return _value;
    }

    //-----------------------------------------------------------------------------
    // Equality operator.
    //-----------------------------------------------------------------------------
    constexpr friend bool operator == (const Type& lhs, const Type& rhs)
    {
        return lhs._value == rhs._value;
    }

    //-----------------------------------------------------------------------------
    // Inequality operator.
    //-----------------------------------------------------------------------------
    constexpr friend bool operator != (const Type& lhs, const Type& rhs)
    {
        return !(lhs == rhs);
    }

private:
    DataType _value;	// The stored value. Default value defined by explicit constructor.
};

#endif

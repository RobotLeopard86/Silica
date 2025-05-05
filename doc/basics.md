# Silica API Basics

## Serialization
Silica has a built-in serialization and deserialization system. It lives in the `silica::serialization` namespace, and can be included from `silica/serialization/<format>.hpp`.  
Each format can serialize either to a string (JSON/YAML), a byte vector (Binary), or an output stream (all). Deserialization supports the inverse.  
There is also a format conversion system found in `silica/serialization/convert.hpp`, to convert between the different formats in-place.

## Reflection
The primary entrypoint for reflection is `silica::reflection::reflect`, from the `silica/reflection/reflection.hpp` header.  

You can either pass in a pointer to an object you wish to reflect, or a Silica `Var` object, which can be used to examine and modify a field.  
Static members can also be accessed by passing in a `nullptr`, but this is not recommended as it can cause issues with other class objects.  

In order for a class to be reflectable, it must have at least one constructor satisfying the  `std::is_default_constructible` type trait.  

When a value is reflected, it returns a `TypeInfo` object, which is not super useful on it's own.
To make it useful, call it's `get` method templated on one of Silica's reflection primitives.  The two most common ones are `Object` and `Enum`, but when working with `Var` objects as mentioned above, you will likely use others.  

`Object` primitives allow you to examine fields and methods, while `Enum` primitives allow you to convert between an enum value and a `std::string`.   The other primitives allow things like checking integer signedness, checking for null pointers, array access, etc. depending on the type.  

When working with methods, it is especially important to ensure correct template arguments, otherwise you will get ugly compile errors.

## Errors
Silica deals with errors by returning `Expected` objects. These can either hold a result value or an error value, which can be checked via the API.  
You can also use the `unwrap` method to return the result and throw an exception if an error value is held.

## A Note on Strings
C `const char*` and STL `std::string_view` objects only reference data owned elsewhere. For this reason, they will be marked as read-only by Silica. Use a `std::string` to own and modify data.

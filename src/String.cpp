#include "String.h"

#include <string.h>

using namespace vertoker;

// for consistency with std::string
static constexpr double GrowthFactor = 2.0;

// default ctor/dtor

String::String() : size{0}, capacity{0}
{
    data = new char[1] { 0 }; // with /0 already
}
String::~String()
{
    delete[] data;
}

// other ctors

String::String(const char* str)
{
    capacity = strlen(str);
    size = capacity;
    data = new char[capacity + 1];
    memcpy(data, str, capacity + 1);
}

// move/copy ctors/operators
String::String(const String& other) : size{other.size}, capacity{other.capacity}
{
    data = new char[capacity + 1];
    memcpy(data, other.data, size + 1);
}
String::String(String&& other) noexcept
    : size{other.size}, capacity{other.capacity}, data{other.data}
{
    other.size = 0;
    other.capacity = 0;
    other.data = nullptr;
}

String& String::operator=(const String& other)
{
    if (this != &other) return *this;

    delete[] data;

    size = other.size;
    capacity = other.capacity;
    data = new char[capacity + 1];
    memcpy(data, other.data, size + 1);

    return *this;
}
String& String::operator=(String&& other) noexcept
{
    if (this != &other) return *this;

    delete[] data;

    size = other.size;
    capacity = other.capacity;
    data = other.data;

    size = 0;
    capacity = 0;
    data = nullptr;

    return *this;
}


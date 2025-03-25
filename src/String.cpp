#include "String.h"

#include <string.h>

using namespace vertoker;

/// default ctor/dtor

String::String()
    : size{ 0 }, capacity{ 0 }
{
    data = new char[ 1 ] { 0 }; // with null-terminated already
}

String::~String()
{
    delete[] data;
}

/// other ctors

String::String( const char* str )
{
    capacity = strlen( str );
    size     = capacity;
    data     = new char[ capacity + 1 ];

    memcpy( data, str, capacity + 1 );
}

String::String( const size_t newSize, const size_t newCapacity, char* newData ) noexcept
    : size{ newSize }, capacity{ newCapacity }, data{ newData }
{
    
}

String::String( const String& other )
    : size{ other.size }, capacity{ other.capacity }
{
    data = new char[ capacity + 1 ];
    memcpy( data, other.data, size + 1 );
}

String::String( String&& other ) noexcept
    : size{ other.size }, capacity{ other.capacity }, data{ other.data }
{
    other.size     = 0;
    other.capacity = 0;
    other.data     = nullptr;
}

/// operators

String& String::operator=( const String& other )
{
    if ( this == &other ) return *this;

    delete[] data;

    size     = other.size;
    capacity = other.capacity;
    data     = new char[ capacity + 1 ];

    memcpy( data, other.data, size + 1 );

    return *this;
}

String& String::operator=( String&& other ) noexcept
{
    if ( this == &other ) return *this;

    delete[] data;

    size     = other.size;
    capacity = other.capacity;
    data     = other.data;

    other.size     = 0;
    other.capacity = 0;
    other.data     = nullptr;

    return *this;
}

void String::operator+=( const String& rhs )
{
    size_t newSize = size + rhs.size;

    if ( capacity < newSize ) Reserve( newSize );
    
    memcpy( data + size, rhs.data, rhs.size + 1 );
}

void String::operator+=( const char* rhs )
{
    size_t rhsSize = strlen( rhs );
    size_t newSize = size + rhsSize;

    if ( capacity < newSize ) Reserve( newSize );
    
    memcpy( data + size, rhs, rhsSize + 1 );
}

// external operators

bool vertoker::operator==( const String& lhs, const String& rhs )
{
    if ( lhs.size != rhs.size ) return false;

    for ( size_t i = 0; i < lhs.size; ++i )
    {
        if ( lhs[ i ] != rhs[ i ] )
            return false;
    }

    return true;
}

bool vertoker::operator==( const String& lhs, const char* rhs )
{
    size_t i = 0;
    for ( ; i < lhs.size; ++i )
    {
        if ( !rhs[ i ] ||            // if lhs.size > rhs.size
            lhs[ i ] != rhs[ i ] )   // if not equal
            return false;
    }

    return !rhs[ i ];                // if lhs.size < rhs.size
}

bool vertoker::operator!=( const String& lhs, const String& rhs )
{
    return !( lhs == rhs );
}

bool vertoker::operator!=( const String& lhs, const char* rhs )
{
    return !( lhs == rhs );
}

String vertoker::operator+( const String& lhs, const String& rhs )
{
    size_t newSize = lhs.size + rhs.size;
    char* newData = new char[ newSize + 1 ];

    memcpy( newData,            lhs.data, lhs.size     );
    memcpy( newData + lhs.size, rhs.data, rhs.size + 1 );
    
    return String( newSize, newSize, newData );
}

String vertoker::operator+( const String& lhs, const char* rhs )
{
    size_t rhsSize = strlen( rhs );
    size_t newSize = lhs.size + rhsSize;
    char* newData = new char[ newSize + 1 ];

    memcpy( newData,            lhs.data, lhs.size    );
    memcpy( newData + lhs.size, rhs,      rhsSize + 1 );
    
    return String( newSize, newSize, newData );
}

std::istream& vertoker::operator>>( std::istream& is, String& str )
{
    char buffer;
    is.get( buffer );

    while ( buffer != '\n' )
    {
        str.PushBack( buffer );
        is.get( buffer );
    }
    
    return is;
}
std::ostream& vertoker::operator<<( std::ostream& os, String& str )
{
    for ( size_t i = 0; i < str.size; ++i )
        os << str[ i ];
    return os;    
}

// functions

void String::Reserve( const size_t newCapacity )
{
    if ( newCapacity <= capacity ) return;

    char* newData = new char[ newCapacity + 1 ];
    if ( data != nullptr )
    {
        memcpy( newData, data, size + 1 );
        delete[] data;
    }

    capacity = newCapacity;
    data     = newData;
}

void String::PushBack( char character )
{
    if ( GetUnusedCapacity() == 0 )
        Reserve( GetNextCapacity() );
    
    data[   size ] = character;
    data[ ++size ] = 0;
}

void String::Clear() noexcept
{
    memset( data, 0, capacity + 1 );
    size = 0;
}

#include <iostream>
#include <algorithm>
#include <vector>

#include <string>
#include "String.h"

struct
{
    bool operator()( vertoker::String& a, vertoker::String& b ) const
    {
        size_t minsize = ( a.GetSize() < b.GetSize() ) ? a.GetSize() : b.GetSize();
    
        for ( size_t i = 0; i < minsize; ++i )
        {
            if ( tolower( a[ i ] ) > tolower( b[ i ] ) ) return true;
            if ( tolower( a[ i ] ) < tolower( b[ i ] ) ) return false;
        }
        return a.GetSize() > b.GetSize();
    }
} lessPred;

int main()
{
    std::vector< vertoker::String > vec;
    vertoker::String buffer;

    while ( std::cin >> buffer )
    {
        if ( buffer == "" ) break;

        vec.push_back( buffer );
        buffer.Clear();
    }

    std::sort( vec.begin(), vec.end(), lessPred );

    //std::cout << vec.size() << std::endl;
    for ( auto& str : vec )
        std::cout << str << std::endl;
    
    std::cin.ignore(); // for console app
    
    return 0;
}

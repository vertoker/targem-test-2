#ifndef __VERTOKER_STRING_H_
#define __VERTOKER_STRING_H_

#include <stddef.h>

#include <iostream>

namespace vertoker
{

    class String
    {
    public:
        // default ctor/dtor
        String();
        ~String();

        // other ctors
        String(const char* str);

        // copy/move ctors/operators
        String(const String& other);
        String(String&& other) noexcept;
        String& operator=(const String& other);
        String& operator=(String&& other) noexcept;
        
        // "fields"
        inline char& operator[](size_t index) const { return data[index]; }

        inline size_t GetSize() const noexcept { return size; }
        inline size_t GetCapacity() const noexcept { return capacity; }
        inline char* GetData() const noexcept { return data; }

    private:
        size_t size;
        size_t capacity;
        char* data;
    };
    
} // namespace vertoker


#endif // __VERTOKER_STRING_H_
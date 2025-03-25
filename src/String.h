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
        String(const size_t newSize, const size_t newCapacity, char* newData);

        // copy/move ctors/operators
        String(const String& other);
        String(String&& other) noexcept;
        String& operator=(const String& other);
        String& operator=(String&& other) noexcept;

        // operators
        friend bool operator==(const String& lhs, const String& rhs);
        friend bool operator==(const String& lhs, const char* rhs);
        friend bool operator!=(const String& lhs, const String& rhs);
        friend bool operator!=(const String& lhs, const char* rhs);

        void operator+=(const String& rhs);
        void operator+=(const char* rhs);

        friend String operator+(const String& lhs, const String& rhs);
        friend String operator+(const String& lhs, const char* rhs);

        friend std::istream& operator>>(std::istream& is, String& str);
        friend std::ostream& operator<<(std::ostream& os, String& str);
        
        // "fields"
        inline char& operator[](size_t index) const { return data[index]; }

        inline size_t GetSize() const noexcept { return size; }
        inline size_t GetCapacity() const noexcept { return capacity; }
        inline char* GetData() const noexcept { return data; }

        // public functions
        void Reserve(const size_t newCapacity);
        void PushBack(char character);
        void Clear() noexcept;

    private:
        // private functions
        size_t GetUnusedCapacity() const;
        size_t GetNextCapacity() const;
        
        // data
        size_t size;
        size_t capacity;
        char* data;
    };

    // external operators
    bool operator==(const String& lhs, const String& rhs);
    bool operator==(const String& lhs, const char* rhs);
    bool operator!=(const String& lhs, const String& rhs);
    bool operator!=(const String& lhs, const char* rhs);

    String operator+(const String& lhs, const String& rhs);
    String operator+(const String& lhs, const char* rhs);

    std::istream& operator>>(std::istream& is, String& str);
    std::ostream& operator<<(std::ostream& os, String& str);

} // namespace vertoker


#endif // __VERTOKER_STRING_H_
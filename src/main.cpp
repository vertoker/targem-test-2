#include <iostream>
#include <algorithm>
#include <vector>

#include <string>
#include "String.h"

int main()
{
    std::vector<vertoker::String> vec;

    vertoker::String buffer;
    while (std::cin >> buffer)
    {
        if (buffer == "") break;
        vec.push_back(buffer);
        buffer.Clear();
    }

    std::cout << vec.size() << std::endl;
    for (auto& str : vec)
        std::cout << str << std::endl;
    
    return 0;
}

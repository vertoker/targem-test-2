#include <iostream>
#include <algorithm>

#include <string>
#include "String.h"

int main()
{
    vertoker::String str1 = "targem test 2";
    vertoker::String str2 = std::move(str1);

    std::cout << str2.GetData() << std::endl;
    return 0;
}

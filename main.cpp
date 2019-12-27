#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include "base64.h"

int main()
{
    std::string str = "abcdefg";
    std::cout << "base64(\"" << str << "\") = \""
              << base64::encode(str.c_str(), str.size()) << "\"\n";
    system("pause");
}
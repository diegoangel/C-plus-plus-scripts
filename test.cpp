#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[])
{
    const char* test_1 = "test_1";
    const char test_2[] = "test_2";
    std::cout << "Escribi algo..." << std::endl;
    std::string test_3;
    std::getline(std::cin, test_3);
    test_1 = test_3.c_str();
    std::cout << test_1 << std::endl;
    std::cout << test_2 << std::endl;
    return 0;
}

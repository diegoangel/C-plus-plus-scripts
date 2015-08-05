#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[])
{
    char c[] = "tu vieja en tanga";
    std::vector<char> v;
    v.push_back(c);
    std::string str = v[0]; 
    std::cout << str << std::endl;

    return 0;
}

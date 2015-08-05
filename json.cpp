#include <json.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>

#include "json.hpp"

// for convenience
using json = nlohmann::json;

int main(int argc, char *argv[]) 
{

std::ifstream conf("conf.conf");

std::string content( 
    (std::istreambuf_iterator<char>(conf)),
    (std::istreambuf_iterator<char>()) 
);

json j = json::parse(content);

json o = json::parse(content);

std::string s = j["server"]["ip"];

std::cout << s << std::endl;

return 0;
}

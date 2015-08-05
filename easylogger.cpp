#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <easylogging++.h>
#include <string>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *arcv[]) {

    std::string conf = "../conf/easylogging++.conf";

    el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
    el::Loggers::addFlag(el::LoggingFlag::HierarchicalLogging);
    el::Configurations confFromFile(conf);
    el::Loggers::reconfigureAllLoggers(confFromFile); 

    exit(EXIT_SUCCESS);
}

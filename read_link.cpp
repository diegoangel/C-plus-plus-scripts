#include <iostream>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <libgen.h>

std::string do_readlink(std::string path) {
    char buff[PATH_MAX];
    ssize_t len = readlink(path.c_str(), buff, sizeof(buff)-1);
    if (len != -1) {
        buff[len] = '\0';
        return std::string(buff);
    }
    /* handle error condition */
}
//If you're only after a fixed path:

std::string get_selfpath() {
    char buff[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buff, sizeof(buff)-1);
    if (len != -1) {
        buff[len] = '\0';
        return std::string(buff);
    }
    /* handle error condition */
}

std::string getSelfPath() {
    char buff[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buff, sizeof(buff)-1);
    if (len != -1) {
        buff[len] = '\0';
        std::string programDirname = std::string(dirname(const_cast<char*>(buff)));
        //std::string programDirname = std::string(programDirname);
        //free(programDirname);
        return programDirname;
    } 
}

//To use it:

int main(int argc, char *argv[])
{

    std::string selfpath = getSelfPath();
    std::cout << selfpath << std::endl;
    return 0;
}

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

int main(int argc, char *argv[])
{
    const char *path = "../info.php";
    std::cout << path << std::endl;
    char *real_path = realpath(path, NULL);
    //char resolved_path[100];
    printf("\n%s\n",real_path);
    free(real_path);
    return 0;
}


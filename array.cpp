#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cstdint>

using namespace std;

int main(int argc, char* argv[]) {

    //int64_t myarray[3] = {549638130622280, 549638130622281, 549638130622282};
    unsigned long myarray[3] = {549638130622280, 549638130622281, 549638130622282};
    //unsigned long long int myarray[3] = {549638130622280, 549638130622281, 549638130622282};

    for (int i=0; i<3; ++i)
        cout <<  myarray[i] << endl;

    return 0;
}





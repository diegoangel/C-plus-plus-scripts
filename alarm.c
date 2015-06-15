#include <stdio.h>
#include <signal.h>

int main() {
    int go = 1;
    alarm(4);
    while(go) {
        printf("sip");
    }
    return 0;
}

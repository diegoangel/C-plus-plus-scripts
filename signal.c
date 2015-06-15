#include <stdio.h>
#include <signal.h>
#include <string.h>   /* for memset */
#include <unistd.h>   /* for sleep and getpid */
#include <stdlib.h>
#include <syslog.h>

int done = 0;

void sighandler(int signal)
{
    const char *signal_name;

    switch (signal) {
        case SIGHUP:
            signal_name = "SIGHUP";
            syslog (LOG_NOTICE, "SIGHUP");             
            break;
        case SIGUSR1:
            signal_name = "SIGUSR1";
            syslog (LOG_NOTICE, "SIGUSR1"); 
            break;
        case SIGINT:
            printf("Caught SIGINT, exiting now\n");
            signal_name = "SIGINT";
            syslog (LOG_NOTICE, "SIGINT");        
            done = 1;
            exit(0);
        case SIGTERM:
            printf("Caught SIGTERM, exiting now\n");
            signal_name = "SIGTERM";      
            syslog (LOG_NOTICE, "SIGTERM");    
            done = 1;
            exit(0); 
        case SIGTSTP:
            printf("Caught SIGTERM, exiting now\n");
            signal_name = "SIGTERM";      
            syslog (LOG_NOTICE, "SIGTERM");
            break;       
        default:
            fprintf(stderr, "Caught wrong signal: %d\n", signal);
            return;
    }
}

int main(void)
{

    openlog ("signal", LOG_PID, LOG_DEBUG);
    
    struct sigaction new_sa;    

    sigemptyset(&new_sa.sa_mask);
    new_sa.sa_flags = 0;
    new_sa.sa_handler = sighandler;
    // Registering handlers
    sigaction(SIGTSTP, &new_sa, NULL);
    sigaction(SIGHUP,  &new_sa, NULL);
    sigaction(SIGINT,  &new_sa, NULL);
    sigaction(SIGTERM, &new_sa, NULL);

    printf("Press ctrl-c, or send SIGTERM to process ID %d, to gracefully exit program.\n", getpid());

    while (!done)
    {
        sleep(1);
        printf("I'm still waiting...\n");
    }

    printf("All done!\n");

    return 0;
}

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <fstream>

const char* sender_email="diegoangel77@gmail.com";

// The emailer
//bool sendmail(const std::string&, const std::string&, const std::string&);

bool sendmail(const std::string& receiver, const std::string& subject, const std::string& message) {
 
    bool success = false;
 
    try {
        FILE *mta = popen("/usr/sbin/sendmail -io -t", "w");
        if (mta != 0) {
            fprintf(mta, "To: %s\n", receiver.c_str());
            fprintf(mta, "From: %s\n", sender_email);
            fprintf(mta, "Subject: %s\n\n", subject.c_str());
            fwrite(message.c_str(), 1, strlen(message.c_str()), mta);
            fwrite(".\n", 1, 2, mta);
 
            pclose(mta);
 
            success = true;
        }
    } catch (...) {
        syslog (LOG_NOTICE, "Error in sending email");     
    }
 
    return success;
}

void LogMessage( const std::string& Message )
{
    static std::ofstream LogFile("/home/diego/Public/www/test/cpp/cdaemon.log");
    if (LogFile.is_open())
    {
        LogFile << Message << std::endl;
    } else {
        std::cout << Message << std::endl;
    }
}

bool exitNow = false;

void handler(int signum) {
    exitNow = true;
    syslog (LOG_NOTICE, "Exit signal received !");
}

int main(int argc, char* argv[]) 
{

std::fstream pidfile;

if ( argc != 2 ) 
    // We print argv[0] assuming it is the program name
    std::cout << "usage: " << argv[0] << " <pidfile>\n";
  else {
    // We assume argv[1] is a filename to open
     pidfile.open(argv[1], std::fstream::in | std::fstream::out | std::fstream::trunc);
    // Always check to see if file opening succeeded
    if ( !pidfile.is_open() ) {
      std::cout<<"Could not open file\n";
    }
  }

    /* Our process ID and Session ID */
    pid_t pid, sid;

    /* Fork off the parent process */
    pid = fork();

    if (pid < 0) {      
        exit(EXIT_FAILURE);
    }

    /* If we got a good PID, then
       we can exit the parent process. */
    if (pid > 0) {           
        exit(EXIT_SUCCESS);
    }
            
    /* Open any logs here */                  

    openlog ("cdaemon", LOG_PID, LOG_DAEMON);

    /* Create a new SID for the child process */
    sid = setsid();

    if (sid < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }

    //--
    /* Catch, ignore and handle signals */
    // Install our signal handler.  This responds to 
    // kill [pid] from the command line
    signal(SIGTERM, handler);
 
    // Ignore signal  when terminal session is closed.  This keeps our
    // daemon alive even when user closed terminal session
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Success: Let the parent terminate */
    if (pid > 0) {
    pidfile << std::to_string(pid) << std::endl;

    pidfile.close();

        exit(EXIT_SUCCESS);
    }
    //--

    /* Change the file mode mask */
    umask(0);

    /* Change the current working directory */
    if ((chdir("/")) < 0) {
            /* Log the failure */
            exit(EXIT_FAILURE);
    }
    
    /* Close out the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    /* Daemon-specific initialization goes here */
    
    /* The Big Loop */
    while (1) {
        /* Do some task here ... */

        if (exitNow) {
            syslog (LOG_NOTICE, "Exiting from the main loop.");
            break;
        }
        //LogMessage(std::to_string(pid)); 

        syslog (LOG_NOTICE, "First daemon started.");

        sleep(3); /* wait 3 seconds */
    }

    syslog (LOG_NOTICE, "First daemon terminated.");
    closelog();

   exit(EXIT_SUCCESS);
}
#include <stdio.h>

int  main()
{
    FILE *out;
    /* the 'popen' fn. executes 'sendmail' as a subprocess &  creates a pipe that
     * subprocess, now one can write/read to the 'out' stream using 'fprintf'/'fscanf'
     * */
    out = popen("/usr/sbin/sendmail -d -oi -t", "w");
    fprintf(out, "To: drivarola@movilgate.com\n");
    fprintf(out, "From: localhost\n");
    fprintf(out, "Subject: testo\n\n");
    fprintf(out, "test message\n");
    pclose(out);
    
    return 0;
}

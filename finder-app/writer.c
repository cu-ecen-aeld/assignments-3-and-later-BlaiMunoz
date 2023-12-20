#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Error: Invalid number of arguments.\n");
        return 1;
    }

    char *writefile = argv[1];
    char *writestr = argv[2];

    FILE *file = fopen(writefile, "w");
    if (file == NULL) {
        printf("Error: Could not create file.\n");
        return 1;
    }

    fprintf(file, "%s", writestr);
    fclose(file);

    openlog("writer", LOG_PID|LOG_CONS, LOG_USER);
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);
    closelog();

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        syslog(LOG_ERR, "Usage: %s <file_path> <string_to_write>", argv[0]);
        exit(1);
    }

    const char *file_path = argv[1];
    const char *string_to_write = argv[2];

    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to open file %s for writing", file_path);
        exit(1);
    }

    fputs(string_to_write, fp);
    fclose(fp);

    syslog(LOG_DEBUG, "Writing \"%s\" to \"%s\"", string_to_write, file_path);

    return 0;
}

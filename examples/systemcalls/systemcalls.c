#include "systemcalls.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdarg.h>

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{
    int status = system(cmd);
    if (status == -1) {
        printf("Failed to execute system command.\n");
        return false;  // Return false if system() call failed
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        return true;  // Return true if system() call completed successfully
    }
    return false;  // Return false if system() call completed with an error
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return false;
    } else if (pid == 0) {  // child process
        execv(command[0], command);
        perror("execv failed");  // only returns if execv fails
        exit(EXIT_FAILURE);
    } else {  // parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            return true;
        } else {
            return false;
        }
    }
}

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];


/*
 * TODO
 *   Call execv, but first using https://stackoverflow.com/a/13784315/1446624 as a refernce,
 *   redirect standard out to a file specified by outputfile.
 *   The rest of the behaviour is same as do_exec()
 *
*/

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return false;
    }

    if (pid == 0) {
        // Child process
        // Open the output file for writing
        FILE* outFile = fopen(outputfile, "w");
        if (outFile == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        // Redirect stdout to the output file
        if (dup2(fileno(outFile), STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        // Execute the command
        if (execv(command[0], command) == -1) {
            perror("execv");
            exit(EXIT_FAILURE);
        }

        // Close the output file
        fclose(outFile);
    } else {
        // Parent process
        int status;
        if (wait(&status) == -1) {
            perror("wait");
            return false;
        }
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            return true;
        } else {
            return false;
        }
    }

    va_end(args);

    return true;
}

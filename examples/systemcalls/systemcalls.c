#include "systemcalls.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <fcntl.h>

bool do_system(const char *cmd) {
    int status = system(cmd);
    if (status == -1) {
        perror("system");
        return false;
    }
    return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

bool do_exec(int count, ...) {
    va_list args;
    va_start(args, count);
    char *command[count + 1];
    int i;
    for (i = 0; i < count; i++) {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        va_end(args);
        return false;
    } else if (pid == 0) { // Child process
        if (execv(command[0], command) == -1) {
            perror("execv");
            exit(EXIT_FAILURE);
        }
    } else { // Parent process
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            va_end(args);
            return false;
        }
        return WIFEXITED(status) && WEXITSTATUS(status) == 0;
    }

    va_end(args);
    return true;
}

bool do_exec_redirect(const char *outputfile, int count, ...) {
    va_list args;
    va_start(args, count);
    char *command[count + 1];
    int i;
    for (i = 0; i < count; i++) {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        va_end(args);
        return false;
    } else if (pid == 0) { // Child process
        int fd = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO); // Redirect stdout to the file
        close(fd);

        if (execv(command[0], command) == -1) {
            perror("execv");
            exit(EXIT_FAILURE);
        }
    } else { // Parent process
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            va_end(args);
            return false;
        }
        return WIFEXITED(status) && WEXITSTATUS(status) == 0;
    }

    va_end(args);
    return true;
}


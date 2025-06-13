#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

#define MAXIMUM_LINE 1024
#define MAXIMUM_ARGS 100
#define HISTORY_SIZE 100

char* history[HISTORY_SIZE];
int historyCount = 0;

void add_to_history(const char* cmd) {
    if (historyCount < HISTORY_SIZE) {
        history[historyCount++] = strdup(cmd);
    }
}

void showHistory() {
    for (int i = 0; i < historyCount; i++) {
        printf("%d. %s\n", i + 1, history[i]);
    }
}

//after pressing Ctrl+C
void sigintHandler(int sig) {
    printf("\nType 'exit' to quit.\nsh> ");
    fflush(stdout);
}

// removes newline character from input
void trimNewline(char* str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// tokenizes a command string into arguments
char** parse_command(char* cmd, int* background) {
    static char* args[MAXIMUM_ARGS];
    int i = 0;
    char* token = strtok(cmd, " ");

    while (token != NULL && i < MAXIMUM_ARGS - 1) {
        if (strcmp(token, "&") == 0) {
            *background = 1;
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " ");
    }

    args[i] = NULL;
    return args;
}

int command(char* cmdline);

void pipeline(char* cmdline) {
    int pipefd[2];
    pid_t pid;
    int fd_in = 0;
    char* cmd = strtok(cmdline, "|");

    while (cmd != NULL) {
        pipe(pipefd);
        pid = fork();

        if (pid == 0) {
            dup2(fd_in, 0); // input redirection
            if (strtok(NULL, "|") != NULL) {
                dup2(pipefd[1], 1); // output redirection
            }
            close(pipefd[0]);
            command(cmd);
            exit(0);
        } else {
            wait(NULL);
            close(pipefd[1]);
            fd_in = pipefd[0];
            cmd = strtok(NULL, "|");
        }
    }
}

// Deals with <, >, >> redirection (output and input)
void redirection(char** args) {
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], ">") == 0) {
            int fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        } else if (strcmp(args[i], ">>") == 0) {
            int fd = open(args[i+1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        } else if (strcmp(args[i], "<") == 0) {
            int fd = open(args[i+1], O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
        }
    }
}

// Runs a command
int command(char* cmdline) {
    int background = 0;
    char* cmd = strdup(cmdline); // copy original line so we can reuse it
    trimNewline(cmd);
    add_to_history(cmd);

    // check piping
    if (strstr(cmd, "|") != NULL) {
        pipeline(cmd);
        return 1;
    }

    // Check  &&
    if (strstr(cmd, "&&") != NULL) {
        char* first = strtok(cmd, "&&");
        char* second = strtok(NULL, "&&");
        if (command(first)) {
            command(second);
        }
        return 1;
    }

    // Check  ";"
    if (strstr(cmd, ";") != NULL) {
        char* token = strtok(cmd, ";");
        while (token != NULL) {
            command(token);
            token = strtok(NULL, ";");
        }
        return 1;
    }


    char** args = parse_command(cmd, &background);
    if (args[0] == NULL) return 0;

   
    if (strcmp(args[0], "exit") == 0) exit(0);
    if (strcmp(args[0], "history") == 0) {
        showHistory();
        return 1;
    }

    // fork and execution
    pid_t pid = fork();
    if (pid == 0) {
        redirection(args);
        execvp(args[0], args);
        perror("error");
        exit(1);
    } else {
        if (!background) wait(NULL);
    }

    return 1;
}


int main() {
    char line[MAXIMUM_LINE];
    signal(SIGINT, sigintHandler);

    while (1) {
        printf("sh> ");
        if (fgets(line, sizeof(line), stdin) == NULL) break;
        command(line);
    }

    return 0;
}

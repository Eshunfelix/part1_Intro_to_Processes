#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void child_process();  // Prototype for child process
void parent_process();  // Prototype for parent process

int main() {
    pid_t pid1, pid2;

    // Fork the first child
    pid1 = fork();
    if (pid1 == 0) {
        child_process();
        exit(0);  // Child exits after completion
    } 
    else {
        // Fork the second child
        pid2 = fork();
        if (pid2 == 0) {
            child_process();
            exit(0);  // Child exits after completion
        }
        else {
            // Parent process waits for both children
            parent_process();
            wait(NULL);  // Wait for first child to finish
            wait(NULL);  // Wait for second child to finish
            printf("Both children have completed.\n");
        }
    }
    return 0;
}

void child_process() {
    srandom(time(NULL));  // Seed the random number generator
    int iterations = random() % 30 + 1;  // Random iterations, max 30
    int i;
    for (i = 0; i < iterations; i++) {
        int sleep_time = random() % 10 + 1;  // Sleep for 1-10 seconds
        printf("Child Pid: %d is going to sleep for %d seconds\n", getpid(), sleep_time);
        sleep(sleep_time);
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
    }
    printf("Child Pid: %d has completed its task.\n", getpid());
}


void parent_process() {
    int status;
    pid_t pid;

    while ((pid = wait(&status)) > 0) {
        printf("Child Pid: %d has completed.\n", pid);
    }
}

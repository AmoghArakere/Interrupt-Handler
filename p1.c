#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signum) {
    if (signum == SIGFPE) {
        printf("Caught divide-by-zero exception. Raising custom signal...\n");
        // Raise the custom signal (SIGUSR1) to notify the kernel module
        kill(getpid(), SIGUSR1);
    }
}

int main() {
    // Set up signal handler for divide-by-zero exception
    signal(SIGFPE, signal_handler);

    // Cause divide-by-zero exception
    int a = 1;
    int b = 0;
    int c = a / b; // This will cause a divide-by-zero exception

    printf("This won't be printed: %d\n", c);

    return 0;
}



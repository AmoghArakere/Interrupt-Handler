
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define DEVICE_PATH "/dev/divzero"
#define IOCTL_CMD _IOR('d', 1, int *)

void signal_handler(int signum) {
    if (signum == SIGFPE) {
        int fd = open(DEVICE_PATH, O_RDWR);
        if (fd < 0) {
            perror("Failed to open device");
            exit(EXIT_FAILURE);
        }
        if (ioctl(fd, IOCTL_CMD) < 0) {
            perror("Failed to send ioctl");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);
        exit(EXIT_SUCCESS);
    }
}

int main() {
    signal(SIGFPE, signal_handler);

    int a = 1;
    int b = 0;
    int c = a / b; // This will cause a divide-by-zero exception

    printf("This won't be printed: %d\n", c);
    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

static void siginth(int signo)
{
    if (signo == SIGINT)
    {
        int file, w;
        file = open("SigInt.txt", O_APPEND | O_WRONLY | O_CREAT, 0644);
        if (file == -1)
        {
            printf("Open SigInt.txt failed: %d, %s\n", errno, strerror(errno));
            exit(1);
        }
        char s[] = "SIGINT CAUGHT";
        w = write(file, s, sizeof(s)-1);
        if (w == -1)
        {
            printf("Writing to SigInt.txt failed: %d, %s\n", errno, strerror(errno));
            exit(1);
        }
        close(file);
        exit(0);
    }
}

static void sigusrh(int signo)
{
    if (signo == SIGUSR1)
    {
        printf("PPID: %d\n", getppid());
    }
}

int main()
{
    signal(SIGINT, siginth); //kill -SIGINT PID
    signal(SIGUSR1, sigusrh); //kill -SIGUSR1 PID
    while (1)
    {
        printf("PID: %d\n", getpid());
        sleep(1);
    }

    return 0;
}
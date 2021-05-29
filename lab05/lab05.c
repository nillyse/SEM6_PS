// PS IS1 321 LAB04
// Roksana Jarema
// jr44346@zut.edu.pl

#include <stdlib.h>
#include <string.h>
#include <utmpx.h>
#include <sys/types.h>
#include <pwd.h>
#include <getopt.h>
#include <stdbool.h>
#include <grp.h>
#include <stdio.h>
#include <dlfcn.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <math.h>

int pid;
bool end_all = false;
bool end_child = false;
int count = 0;

void end_program_signal(int no, siginfo_t *info, void *ucontext) //sigint
{
    end_all = true;
}

char *actimeWrap()
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char *timeString = asctime(timeinfo);
    int dateLength = strlen(timeString);
    for (int i = 0; i < dateLength; i++)
        if (timeString[i] == '\n')
            timeString[i] = ' ';
    return timeString;
}
void child_signal(int no, siginfo_t *info, void *ucontext) //sigchld
{
    printf("         [%d] [%d] [%s]\n", info->si_pid, info->si_status, actimeWrap());
    count--;
    if (end_all && count == 0)
        exit(0);
}

void child_alarm_signal(int no, siginfo_t *info, void *ucontext) //sigalrm
{
    end_child = true;
}

int factor(int sec)
{
    printf("[%d] [%d] [%s]\n", getpid(), sec, actimeWrap());

    int result = 1;
    int i = 2;
    while (!end_child) {
        result *= i++;
    }
    exit(sec);
}

int main(int argc, char **argv)
{
    int max, gap;
    int arg = getopt(argc, argv, "w:m:");
    while (arg != -1)
    {
        if ((char)arg == 'w')
            gap = atoi(optarg);
        if ((char)arg == 'm')
            max = atoi(optarg);
        arg = getopt(argc, argv, "w:m:");
    }
    if (argc != 5) {
        printf("Brak argumentów\n");
        exit(0);
    }
    struct sigaction sa;
    sa.sa_sigaction = end_program_signal;
    sigemptyset(&(sa.sa_mask));
    sa.sa_flags = SA_SIGINFO;
    int x = sigaction(SIGINT, &sa, NULL);

    struct sigaction sa2;
    sa2.sa_sigaction = child_signal;
    sigemptyset(&(sa2.sa_mask));
    sa2.sa_flags = SA_SIGINFO;
    int y = sigaction(SIGCHLD, &sa2, NULL);

    struct sigaction sa3;
    sa3.sa_sigaction = child_alarm_signal;
    sigemptyset(&(sa3.sa_mask));
    sa3.sa_flags = SA_SIGINFO;
    int z = sigaction(SIGALRM, &sa3, NULL);

    int rand_num;
    double start_time, tmp;
    while (true)
    { //pid == 0
        if (!end_all)
        {
            pid = fork();
            if (pid == 0)
            {
                srand(time(NULL));
                rand_num = rand() % max + 1;
                alarm(rand_num);
                factor(rand_num);
            }
            count++;
        }
        start_time = time(NULL);
        do
        {
            tmp = time(NULL);
            //printf("%f\n", tmp - start_time);
        } while ((tmp - start_time) < gap);
        if (end_all && count == 0)
            break;
    }
}

// gcc lab05.c -o lab05
// ./lab05 -w 3 -m 12
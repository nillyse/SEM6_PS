// PS IS1 321 LAB06
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
#include <pthread.h>
#include "44346.ps.lab06.timer.h"

void halt_the_thread(int no)
{
    printf("\tTid:%ld Time: %f\n", pthread_self(), stop());
    pthread_exit(0);
}

void *factor()
{
    start();
    int result = 1;
    int i = 2;
    while (true)
    {
        result *= i++;
    }
}

int main(int argc, char **argv)
{

    int max, thread_number;
    int arg = getopt(argc, argv, "m:t:");
    while (arg != -1)
    {
        if ((char)arg == 'm')
            max = atoi(optarg);
        if ((char)arg == 't')
            thread_number = atoi(optarg);
        arg = getopt(argc, argv, "m:t:");
    }
    if (argc != 5)
    {
        printf("Brak argumentów\n");
        exit(0);
    }

    struct sigaction act;
    act.sa_handler = halt_the_thread;
    act.sa_flags = 0;
    sigemptyset(&(act.sa_mask));
    sigaction(SIGINT, &act, NULL);

    pthread_t *thread_id = malloc(thread_number * sizeof(pthread_t));
    int *time_per_thread = malloc(thread_number * sizeof(int));

    srand(time(NULL));

    long int start_time;
    for (int i = 0; i < thread_number; i++)
    {

        time_per_thread[i] = rand() % max + 1;
        start_time = time(NULL);
        pthread_create(&thread_id[i], NULL, factor, NULL);
        printf("Tid: %ld Time: %d\n", thread_id[i], time_per_thread[i]);
    }

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    int active_threads = thread_number;
    long int current_time;
    do
    {
        current_time = time(NULL);
        for (int i = 0; i < thread_number; i++)
        {
            if (current_time - start_time >= time_per_thread[i] && time_per_thread[i] != 0)
            {
                pthread_kill(thread_id[i], SIGINT);
                pthread_join(thread_id[i], NULL);
                time_per_thread[i] = 0;
                active_threads--;
            }
        }
    } while (active_threads != 0);
    exit(0);
}
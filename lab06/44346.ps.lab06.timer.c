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

static pthread_key_t counterKey;
static pthread_once_t counterOnce = PTHREAD_ONCE_INIT;

static void freeMemory(void *buffer)
{
    free(buffer);
}

static void createKey(void)
{
    pthread_key_create(&counterKey, freeMemory);
}

void start()
{
    long *start_time;
    pthread_once(&counterOnce, createKey);
    start_time = pthread_getspecific(counterKey);
    if (start_time == NULL)
    {
        start_time = malloc(sizeof(long));
        pthread_setspecific(counterKey, start_time);
    }
    *start_time = time(NULL);
}

float stop()
{
    long stop = time(NULL);
    long *start_time = pthread_getspecific(counterKey);
    return stop - *start_time;
}

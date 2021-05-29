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

#define BILLION 1E9

double calculate_av(double *accum, int count){
    double sum = 0;
    for (int i = 0; i < count; i++){
        sum += accum[i];
    }
    return sum/count;
}

int main(int argc, char **argv){
    bool v = false;
    bool t = false;
    int count;
    int index;
    char *filename;
    char **argv_copy;
    int arg = getopt(argc, argv, "+vt:");
    while(arg!=-1){
        if((char)arg == 'v') {
            v = true;
        }
        if((char)arg == 't') {
            t = true;
            count = atoi(optarg);
        }
        arg = getopt(argc, argv, "+vt:");
    }
    int number = argc - optind;
    filename = argv[optind];
    char **nazwa = malloc((number+1) * sizeof(char*));

    for(int i = 0; i<number; i++)
        nazwa[i] = argv[optind + i];
    nazwa[number] = NULL;


    if(!t) {
        count = 1; 
    }

    int pid;
    struct rusage rusage;
    int *wstatus; 
    struct timespec requestStart, requestEnd;    
    double *accum = (double *)malloc(count *sizeof(double));
    double *accum_user = (double *)malloc(count *sizeof(double));
    double *accum_system = (double *)malloc(count *sizeof(double));
    for(int i=0;i<count; i++){
        clock_gettime(CLOCK_REALTIME, &requestStart);
        pid = fork();
        if(pid==0) {
            if(!v) {
                close(1); 
                close(2); 
                int h = open("/dev/null", O_WRONLY); 
                dup2(h, 1);
                dup2(h, 2);
            }
            execvp(filename, nazwa); 
            return -1;
        }
        wait4(pid, wstatus, 0, &rusage);
        clock_gettime(CLOCK_REALTIME, &requestEnd);
        accum[i] = ( requestEnd.tv_sec - requestStart.tv_sec ) + ( requestEnd.tv_nsec - requestStart.tv_nsec ) / 1E9;
        accum_user[i] = (double)rusage.ru_utime.tv_sec + (double)rusage.ru_utime.tv_usec / 1E6;
        accum_system[i] = (double)rusage.ru_stime.tv_sec + (double)rusage.ru_stime.tv_usec / 1E6;
        printf("real:%f\tuser:%f\tsystem:%f\n", accum[i], accum_user[i], accum_system[i]);
    }
    if(count !=1)
        printf("\nreal:%f\tuser:%f\tsystem:%f\n", calculate_av(accum, count), calculate_av(accum_user, count), calculate_av(accum_system, count));



    return 0;
}

// gcc 44346.ps.lab04.main.c
// ./a.out -v -t 3 ./program_testowy
// ./a.out -t 4 ./program_testowy
// ./a.out ./program_testowy
// ./a.out ./program_testowy_sys
// ./a.out -v ls -l
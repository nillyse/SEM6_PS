#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char **argv){
    struct rusage a;
    for (int i = 0; i < 1000000; i++)
        getrusage(RUSAGE_SELF, &a);
}
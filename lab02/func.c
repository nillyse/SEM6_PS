#include <pwd.h>
#include <stdio.h>

void print_uid(struct passwd *pass) {
    printf("%d\n", pass->pw_uid);

}
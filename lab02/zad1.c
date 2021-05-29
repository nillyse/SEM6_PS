#include <stdlib.h>
#include <string.h>
#include <utmpx.h>
#include <sys/types.h>
#include <pwd.h>

int main()
{
    struct utmpx *ut; //var/run/utmp
    struct passwd *pass; //etc/passwd
    while (1)
    {
        ut = getutxent();
        if(ut== NULL)
            break;
        if(ut->ut_type== 7){
            
            printf("%s\n", ut->ut_user);
            pass = getpwnam(ut->ut_user);
            printf("%d\n", pass->pw_uid);
        }
    }

    return 0;
}
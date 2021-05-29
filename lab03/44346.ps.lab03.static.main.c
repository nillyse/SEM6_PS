// PS IS1 321 LAB02 
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

struct groups_list{
    int ngroups;
    char **groups;
};

struct groups_list get_groups(char* user, int group_id);


int main(int argc, char **argv){
    bool h = false;
    bool g = false;
    int arg = getopt(argc, argv, "hg");;
    while(arg!=-1){
        if((char)arg == 'h') 
            h = true;
        if((char)arg == 'g')
            g = true;
        arg = getopt(argc, argv, "hg");
    }




    struct utmpx *ut; //var/run/utmp
    struct passwd *pass; //etc/passwd

    // ut = getutxent();
    // int ngroups = 0;
    // gid_t *groups;
    // pass = getpwnam("nillyse");
    // int a = getgrouplist("nillyse", pass->pw_gid, groups, &ngroups);


    while (1)
    {
        ut = getutxent();
        if(ut== NULL)
            break;
        if(ut->ut_type== 7){
            pass = getpwnam(ut->ut_user);

            printf("%s ", ut->ut_user);
            if (h)
                printf("(%s) ", ut->ut_host);
            if (g) {
                struct groups_list list = get_groups(ut->ut_user, pass->pw_gid);
                printf("[");
                for(int i=0; i<list.ngroups-1; i++){
                    printf("%s, ", list.groups[i]);
                    free(list.groups[i]);
                }
                printf("%s]", list.groups[list.ngroups-1]);
                free(list.groups);                
            }
            printf("\n");

            
            //printf("%d\n", pass->pw_uid);
        }
    }
    
    return 0;
}
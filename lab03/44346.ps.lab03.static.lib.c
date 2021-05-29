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
#include <string.h>

struct groups_list{
    int ngroups;
    char **groups;
};

struct groups_list get_groups(char* user, int group_id) {
    struct groups_list list;
    list.ngroups = 0;
    gid_t *groups_id = NULL;
    getgrouplist(user, group_id, groups_id, &list.ngroups);
    groups_id = malloc(list.ngroups * sizeof(gid_t));
    getgrouplist(user, group_id, groups_id, &list.ngroups);
    list.groups = (char**)malloc(list.ngroups * sizeof(char*));
    for (int j = 0; j < list.ngroups; j++) {
        list.groups[j] = malloc(sizeof(char) * strlen(getgrgid(groups_id[j])->gr_name));
        strcpy(list.groups[j], getgrgid(groups_id[j])->gr_name);
    }
    free(groups_id);
    return list;

}
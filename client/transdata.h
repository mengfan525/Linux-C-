#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Group
{
    user_number[10];
}

struct Userinfo
{
    char user_number[10];
    char user_name[10];
    char user_pwd[10];
    char user_to[10];
    struct Group groups[10];
}

struct Trans_data
{
    char cmd[10];
    struct Userinfo userdata;
    int file_flag;
    char buff[4096];    
};
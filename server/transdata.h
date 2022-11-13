#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum transdata_cmd{
	CMD_REGISTER        = 0,
	CMD_LOGIN           = 1,
	CMD_PRIVATE_CHAT    = 2,
	CMD_GROUP_CHAT      = 3,
	CMD_BUILD_GROUP     = 4,
	CMD_JION_GROUP      = 5,
	CMD_SHOW_GROUP      = 6,
	CMD_ADD_FRIEND      = 7,
	CMD_SHOW_FRIEND     = 8,
	CMD_SEND_FILE       = 9,
};

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
}Userinfo;

struct Trans_data
{
    int fd;
    int cmd;
    Userinfo userdata;
    int file_flag;
    char buff[4096];    
}Trans_data;


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


struct SockInfo
{
    struct sockaddr_in addr;
    int fd;
    
};
void* working(void* arg);

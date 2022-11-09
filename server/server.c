#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

struct SockInfo
{
    struct sockaddr_in addr;
    int fd;
    
};

struct SockInfo infos[512];


void* working(void* arg);

int main(){
    //1.创建监听的套接字
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1){
        perror("socket");
        return -1;
    }

    //2.绑定本地的IP、 port
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9888);
    saddr.sin_addr.s_addr = INADDR_ANY;  //代表本机所有IP，有三个网卡就有三个IP
    int ret = bind(fd,(struct socketaddr*)&saddr,sizeof(saddr));
    if(ret == -1){
        perror("socket");
        return -1;
    }
    //3.设置监听
    int lis = listen(fd,128);
    if(lis == -1){
        perror("socket");
        return -1;
    }
    //设置同时通信的数量
    int max = sizeof(infos)/ sizeof(infos[0]);
    for(int i = 0;i < max; ++i)
    {
        bzero(&infos[i],sizeof(infos[i]));
        infos[i].fd = -1;
    }

    //4.阻塞并等待客户端的连接
    
    int addrlen = sizeof(struct sockaddr_in);
    while(1){
        struct SockInfo* pinfo;
        for(int i = 0; i< max ;++i)
        {
            if(infos[i].fd == -1)
            {
                pinfo = &infos[i];
                break;
            }
        }
        
        int cfd = accept(fd,(struct socketaddr*)&pinfo->addr,&addrlen);
        pinfo->fd = cfd;
        if(cfd == -1)
        {
            perror("accept");
            break;
        }
        //创建子线程
        pthread_t tid;
        pthread_create(&tid,NULL,working,pinfo);
        pthread_detach(tid);
    }
    close(fd);
    return 0;
}

void *working(void * arg){

    struct SockInfo* pinfo = (struct SockInfo*)arg;

    //连接成功建立，打印客户端的IP和端口信息
    char ip[32];
    printf("client IP: %s,port:%d\n",inet_ntop(AF_INET,&pinfo->addr.sin_addr.s_addr,ip,sizeof(ip)),ntohs(pinfo->addr.sin_port));


    while(1)
    {

        char buff[1024];
        int len = recv(pinfo->fd,buff,sizeof(buff),0);
        if(len > 0)
        {
            printf("client say: %s\n",buff);
            send(pinfo->fd,buff,len,0);
        }
        else if(len == 0)
        {
            printf("client disconnect\n");
            break;
        }
        else
        {
            perror("recv");
            break;
        }    
    }
    close(pinfo->fd);
    pinfo->fd = -1;

    return NULL;
}
#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <arpa/inet.h>
#include  <sys/types.h>
#include  <sys/socket.h>



int main(){
    //1.创建监听的套接字
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1){
        perror("socket");
        return -1;
    }

    //2.连接服务器的IP、 port
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9888);
    inet_pton(AF_INET,"127.0.0.1",&saddr.sin_addr.s_addr);

    int ret = connect(fd,(struct socketaddr*)&saddr,sizeof(saddr));
    if(ret == -1){
        perror("connet");
        return -1;
    }
    //3.通信

    int number = 0;
    while(1)
    {
        //发送数据
        char buff[1024];
        sprintf(buff,"hellod,world,%d...\n",number++);
        send(fd,buff,strlen(buff)+1,0);
        //接受数据
        memset(buff,0,sizeof(buff));

        int len = recv(fd,buff,sizeof(buff),0);
        if(len > 0)
        {
            printf("server say: %s\n",buff);
        }
        else if(len == 0)
        {
            printf("server disconnect\n");
            break;
        }
        else
        {
            perror("recv");
            break;
        }    
        sleep(1);
    }

    close(fd);

    return 0;
}
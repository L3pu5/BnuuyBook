#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main () {
    printf("Opening socket");
    int s, connfd = 0;
    char sendBuff[1025];
    struct sockaddr_in serv_addr;

    s = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(s, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(s, 10);

    const char* minimalReply = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\nContent-Type: text/plain; charset=utf-8\r\n\r\nHello World!";

    //char readBuff[1025];

    while(1) {
        connfd = accept(s, NULL, NULL);
        //snprintf(sendBuff, sizeof(sendBuff), "%s", "Hello World!");
        write(connfd, minimalReply, strlen(minimalReply));
        //read( connfd, readBuff, 1025);
        //printf("RECV: %s\n", readBuff);
        close(connfd);
    }

    return 0;
}
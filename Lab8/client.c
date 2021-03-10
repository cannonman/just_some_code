#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
 
int main()
{
    int CreateSocket = 0,n = 0;
    char data[256]="message";
    struct sockaddr_in ipOfServer;
 
 
    if((CreateSocket = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("Socket not created \n");
        return 1;
    }
 
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(1111);
    ipOfServer.sin_addr.s_addr = inet_addr("127.0.0.1");
 
    connect(CreateSocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer));
	
    write(CreateSocket, data, strlen(data)-1); 
    read(CreateSocket, data, sizeof(data)-1);
    printf("%s", data);
 
    if( n < 0)
    {
        printf("Standard input error \n");
    }
 
    return 0;
}

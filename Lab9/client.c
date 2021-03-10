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
#include <netinet/in.h>
#include <fcntl.h>
char buffer[80]; 
int main()
{

    int CreateSocket = 0,n = 0;
    if((CreateSocket = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("Socket not created \n");
        return 1;
    }
    char data[256]="message";
    struct sockaddr_in ipOfServer;
    fd_set fdset; 

    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(1111);
    ipOfServer.sin_addr.s_addr = inet_addr("127.0.0.1");

    FD_ZERO(&fdset);
 
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(1111);
    ipOfServer.sin_addr.s_addr = inet_addr("127.0.0.1");
 
    connect(CreateSocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer));
 
 while(true)
{
        FD_SET(CreateSocket, &fdset);
        FD_SET(STDIN_FILENO, &fdset);
        int maximum;
	if (CreateSocket > STDIN_FILENO) maximum = CreateSocket;
	else maximum = STDIN_FILENO;
        select(maximum+1, &fdset, NULL, NULL, NULL);
        if(FD_ISSET(CreateSocket, &fdset))
        {
            bzero(buffer, 80);
            read(CreateSocket,buffer,sizeof(buffer));
            printf("Otrzymano komunikat: %s\n", buffer);

        }
        if(FD_ISSET(STDIN_FILENO, &fdset))
        {
            bzero(buffer, 80);
            int n =0;
            while ((buffer[n++] = getchar()) != '\n') 
            ; 
            write(CreateSocket, buffer, sizeof(buffer));
            if (strncmp("exit", buffer, 4) == 0) { 
                printf("quitting...\n"); 
                break;
            }

        }
    }
 
    if( n < 0)
    {
        printf("Standard input error \n");
    }
 
    return 0;
}

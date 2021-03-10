#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
int max(int a, int b[], int c){
	int max = a;
	for (int i = 0; i<c; i++)
		if(b[i]>max)
			max = b[i];
return max;	
 }
int main()
{
	fd_set fdset;
	char buffer[80];
	int clintListn = 0, skip=0;
	int clients_skip[10];
	int clients, client_tab[10];
	struct sockaddr_in ipOfServer;
	clintListn = socket(AF_INET, SOCK_STREAM, 0);
	int udpListn = socket(AF_INET, SOCK_DGRAM, 0);
	ipOfServer.sin_family = AF_INET;
	ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
	ipOfServer.sin_port = htons(1111);
	bind(clintListn, (struct sockaddr*)&ipOfServer , sizeof(ipOfServer));
	bind(udpListn, (struct sockaddr*)&ipOfServer, sizeof(ipOfServer));
	listen(clintListn , 20);
	FD_ZERO(&fdset);
	int pid;
 
while(1)
    {
        FD_SET(clintListn, &fdset);
	FD_SET(udpListn, &fdset);
        for(int i = 0; i<clients; i++)
            FD_SET(client_tab[i],&fdset);
        int maximum = max(clintListn, client_tab, clients);
	if(udpListn > maximum) maximum = udpListn;
        select(maximum+1, &fdset, NULL, NULL, NULL);
        if(FD_ISSET(clintListn, &fdset)){
            client_tab[clients] = accept(clintListn,0,0);
            clients++;
            printf("new connection\n");

        }
        for(int i = 0; i <clients; i++){
            int skip = 0;
            for(int j = 0; j < skip; j++){
                if( i == clients_skip[j])
                    skip = 1;

            }
            if(skip == 1)
                continue;
            
            if(FD_ISSET(client_tab[i], &fdset)){
                bzero(buffer, 80);
                int res = read(client_tab[i],buffer,sizeof(buffer));
                if(res == 0 ){
                    printf("disconnect\n");
                    break;
                }
                if (strncmp("exit", buffer, 4) == 0) { 
                    shutdown(client_tab[i],SHUT_RDWR);
                    clients_skip[skip] = i;
                    skip++;
                    printf("quit\n"); 
                    break;
                }
                    
                printf("message: %s\n", buffer);
                for(int a = 0; a<clients; a++){
                    int skip = 0;
                    for(int j = 0; j < skip; j++){
                        if( a == clients_skip[j])
                            skip = 1;
                    }
                    if(skip == 1)
                        continue;
                    res = write(client_tab[a], buffer, sizeof(buffer));
                }
            }
        }
    } 
     return 0;
}

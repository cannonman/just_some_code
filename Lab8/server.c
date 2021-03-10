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
 
int main()
{
	char data[256];
	int clintListn = 0, clintConnt = 0;
	struct sockaddr_in ipOfServer;
	clintListn = socket(AF_INET, SOCK_STREAM, 0);
	ipOfServer.sin_family = AF_INET;
	ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
	ipOfServer.sin_port = htons(1111);
	bind(clintListn, (struct sockaddr*)&ipOfServer , sizeof(ipOfServer));
	listen(clintListn , 20);
 
	while(1)
	{
		printf("Server is running\n");
		clintConnt = accept(clintListn, (struct sockaddr*)NULL, NULL);
 		read(clintConnt, data, sizeof(data)-1);
		printf(data);
		
		write(clintConnt, data, strlen(data));
 
        close(clintConnt);
        sleep(1);
     }
 
     return 0;
}

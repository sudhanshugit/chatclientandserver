#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "ip_check.h"
int main(int argc, char * argv[])
{
	char ip[20];
	strcpy(ip,argv[1]);
	int valid = ip_check(argc,ip,argv[2]);
	if (!valid){ exit(1);}
	int port=atoi(argv[2]);
	printf ("port no.=%d\n",port);
	int sockfd;
	struct sockaddr_in tels;
	struct sockaddr_in telc;
	int x;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if (sockfd==-1)
		printf ("socket not created\n");
	else
		printf ("socket created\n");
	tels.sin_family=AF_INET;
	tels.sin_port=htons(port);
	tels.sin_addr.s_addr=inet_addr(argv[1]);
	int sin_size=sizeof(struct sockaddr);
	x = bind(sockfd,(struct sockaddr*) &tels,sin_size);
	if (x <0)
		printf ("bind failed\n");
	else
		printf ("bind done\n");
	x=listen(sockfd,4);
	if (x<0)
		printf ("not listening\n");
	else
		printf ("waiting for incoming connection......\n");
	sin_size=sizeof(struct sockaddr);
	int newfd=accept(sockfd,(struct sockaddr *)&telc,&sin_size);
	if (newfd<0)
		printf ("connection failed\n");
	else
		printf ("connection accepted\n");
	char cmd[100];
	char ch[200];
	while(strcmp(cmd,"exit")!=0)
	{
		memset(ch,'\0',200);
		memset(cmd,'\0',100);
		x=recv(newfd,cmd,100,0);
//		printf ("%s:: cmd before cat\n",cmd);
		if (x<0)
			printf ("command not recieved\n");
		else
		{
			char *ch1=" 2>&1|tee me";
			strcat(cmd,ch1);
			//puts(cmd);
			int ret = system(cmd);
			FILE* fp=fopen("me","r");
			while (fgets(ch,200,fp)!= NULL)
			{
				if (send(newfd,ch,200,0)<0)
					printf ("send failed\n");
			//	printf ("test of send :: %s\n",ch);
			}
			//pclose(fp);
			//ch1 = "@$%";
			x=send (newfd,"@$%",200,0);
			if (x<0)
				puts("send failed\n");
		}
//		close(sockfd);
	//memset(ch,'\0',200)
	}
	close(sockfd);
	return 0;
}

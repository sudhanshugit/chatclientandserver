#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include "ip_check.h"
int main(int argc, char *argv[])
{
//	puts(argv[1]);
// 	*error prone area may be the user is mad and the game is of */
//	*if he enters a big garbage value.			    */

	char ip[20]; strcpy(ip,argv[1]);
	int valid = ip_check(argc,ip,argv[2]);
	//puts(argv[1]);
	//int port = atoi(argv[2]);
	if (!valid){exit(1);}
	int port1= atoi(argv[2]);
	printf ("server on port no. = %d\n",port1);
	int sockfd;
	struct sockaddr_in telc;
	struct hostent *he;
	puts(argv[1]);
	//puts(argv[1]);
	if ((he = gethostbyname(argv[1]))==NULL) puts("error in ip add\n");
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if (sockfd<0)
		printf ("socket not created\n");
	else
		printf ("socket created\n");
	telc.sin_family=AF_INET;
	telc.sin_port=htons(port1);
//	char *ipadd;
//	ipadd=strcpy(ipadd,argv[1]);
//	if ((he = gethostbyname(argv[1]))==NULL) puts("error in ip add\n");
	printf(" connection on ip= %s\n",argv[1]);puts(argv[1]);
	telc.sin_addr=*((struct in_addr *)he->h_addr);
	memset(&(telc.sin_zero),'\0',8);
//		printf ("socket created\n");
	int x=connect(sockfd,(struct sockaddr *)&telc,sizeof(struct sockaddr));
	if (x<0)
		{printf ("connection refused\n");perror("connection :");}
	else
		printf("connection accepted\n");
	char cmd[100];
	while(strcmp(cmd,"exit")!=0)
	{
//		memset(ch,'\0',200);
                memset(cmd,'\0',100);

		gets(cmd);
		x=send(sockfd,cmd,100,0);
//		puts(cmd);
		if (x<0)
			printf ("cmd not sent\n");
		char ch[200];
//		while(strcmp(ch,"@$%")!=0)
		do
		{
//			puts(ch);
			x=recv(sockfd,ch,200,0);
//			printf("test of recv %s\n",ch);
			if (x<0)
				printf ("recv failed\n");
			printf("%s",ch);
		} while(strcmp(ch,"@$%")!=0);
		memset(ch,'\0',200);
//		memset(cmd,'\0',100);
		//close(sockfd);
	}
	close(sockfd);
	return 0;
}

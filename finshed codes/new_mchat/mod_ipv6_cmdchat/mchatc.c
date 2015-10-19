// multiple chat client 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>
#define MYPORT "3228"
//#include "ip_check.h"
int main(int argc, char * argv[1])
{
	if (argc < 3){puts("error enter ip\n your id and your freinds id\n as 3 args \n"); exit(1);}
/*******************no need of these now as getaddrinfo will take care of ip*******/
/*	char ip[20];
	strcpy(ip,argv[1]);
	puts(ip);
	int valid = ip_check(ip);
	if (!valid) exit(1);
	//int port=atoi(argv[2]);
	int sockfd;
	char msg[200];
	struct sockaddr_in server;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if (sockfd==-1)
		printf ("error in creating in socket\n");
	server.sin_family=AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_port=htons(MYPORT);
	if (connect(sockfd,(struct sockaddr *)&server ,sizeof(server))<0) */
	int status;
	struct addrinfo hints;// to transfer the data
	struct addrinfo *serv_info;// will get the result of the getaddrinfo
	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_flags=AI_PASSIVE; // TO FILL IN MY IP  :)
	if ((status=getaddrinfo(argv[1],MYPORT,&hints,&serv_info))!=0)
		perror("getaddrinfo error:");
	int sockfd=socket(serv_info->ai_family,serv_info->ai_socktype,serv_info->ai_protocol);
	if (sockfd==-1) {perror("socket failed:"); exit(1);}
	int con_status=connect(sockfd,serv_info->ai_addr,serv_info->ai_addrlen);
	if (con_status==-1)	{perror("connection error");exit(1);}
	else puts("connected\n");
	char msg_srvr[200];
	recv(sockfd,msg_srvr,200,0);
	puts(msg_srvr);
	send(sockfd,argv[2],50,0);// my name
	send(sockfd,argv[3],50,0);// my friend's name
	int x=fork();
	if (x!=0)
	{
		while (1)
		{
			char msgs[200];
//			scanf("%[^\n]s",msgs);
			gets(msgs);//puts("\nhare");
//			if (!strcmp(msgs,NULL)) continue;
			if (!strcmp(msgs,"exit")) 
			{
                        /*      	 exit(1);
                                 close(sockfd);
                                 if (x!=0)
				if (send(sockfd,msgs,200,0)<0)
                                perror("send error:");
                                        kill(x,SIGTERM);*/
				if (send(sockfd,msgs,200,0)<0)
                                	perror("send error:");
				goto end;
                       }
			if (send(sockfd,(msgs),200,0)<0)
				perror("send error:");
			memset(msgs,'\0',200);
		}
	}
	else
	{
		char msgr[200];
		while(1) {
		if (recv(sockfd,msgr,200,0)<0)
		{
			printf ("recvin failed\n");
			perror("recv :: ");
			return 1;
		}
		else
		{
			printf("he/she ::");
			printf ("%s\n",msgr);
		}
		if (!strcmp(msgr,"exit"))
		{
                               /* exit(1);
                                 close(sockfd);
                                 if (x!=0)
                                   kill(x,SIGTERM);*/
				printf("other side logged off\n");
				goto end;
                }
		}
	}
	//printf("msg reply ::%s \n",msg);
	//char msg_r[2000]="\nhiiiii thanks for connection\n";
//	if (send(sockfd,msg_r,200,0)<0&&printf ("kumar\n"))
//		printf ("message not sent\n");
//	int x;
	//printf ("for reply enter :: r\n");
//	printf("please enter 200 char at a time only\n");
//	printf ("to exit press ctrl + c");
/*	while(1)
	{
		char msg_s[250],msg_r[250];
		scanf("%s",msg_s);
		if (send(sockfd,msg_s,250,0)<0)
			printf ("msg not sent\n");
		if (recv(sockfd,msg_r,250,0)<0)
			printf ("recv error\n");
			int retr=system(msg_r);
			return (retr);
		puts(msg_r);
	}*/
//	puts("reply \n");
//	puts(msg_r);
	end:  ;
	puts("logging of chat\n");
	if (x!=0)
		kill(x,SIGTERM);
	close(sockfd);
	return 0;
}


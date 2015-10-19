#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#define MYPORT 3490
#include <stdlib.h>
#include <signal.h>
#include "ip_check.h"
int main(int argc,char *argv[])
{
	if (argc < 2) {puts ("error enter ip and port no. as 2 arg."); exit(1);}
	char ip[20];
	strcpy(ip,argv[1]);
	puts(ip);
	int valid = ip_check(argc,ip,argv[2]);
	if (!valid) exit(1);
	int port=atoi(argv[2]);
	int sockfd;
	struct sockaddr_in my_addr,their_addr;
	sockfd= socket(AF_INET,SOCK_STREAM,0);
	if (sockfd <0)
		printf ("socket creation failed\n");
	printf ("socket successful\n");
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr =  INADDR_ANY;
	//memset(&(my_addr.sin_zero),'\0',8);
	//if (setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int))==-1)
	//{	perror("setsockopt"); exit (1);}
	int x = bind(sockfd,(struct sockaddr *)&my_addr, sizeof(struct sockaddr));
	if (x<0)
		{printf ("the binding failed\n");perror("bind :");}
	else
	{
		puts ("bind done\n");
	}
	if (listen(sockfd,10)<0)
		printf ("the listening failed\n");
	puts("waiting for incoming connection...\n");
	int sin_size= sizeof(struct sockaddr_in);
	int new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
	if (new_fd<0)
		printf ("connection not accepted\n");
	puts("connection accepted\n");
//	printf ("check\n");
//	int msg_len;
//	char *reply;
//	char *msgs="so chating started enjoy :) \n";
//	write (sockfd,msgs,20);
//	msg_len=send(new_fd,msgs,strlen(msgs),0);
//	if (msg_len<0)
//	{
//		printf ("sending failed\n");
//		puts("check\n");
//	}
/*	char reply[200];//="fakjdslfkja";
	if (msg_len= recv(new_fd,reply,200,0)<0)
	{
		printf ("receive failed %d\n",msg_len);
		perror("recv ::");
	}*/
//	printf("msglen:: %d",msg_len);
//	system(reply);
//	reply[msg_len+1]='\0';
//	printf ("the reply is :: %s\n",reply);
//	puts(reply);
	x=fork();
//	while(1){
	if (x!=0)
	{
		while(1)
	        {
        	        char msg_s[200];
//			printf ("me ::");
			gets(msg_s);
//			printf ("\n");
			if (!strcmp(msg_s,"exit"))
			{
				/*exit(1);
				 close(sockfd);
				 if (x!=0)
                			kill(x,SIGTERM);*/
				if (send(new_fd,msg_s,200,0)<0)
                                printf ("msg not sent\n");

				goto end;
			}

//                	scanf("%[^\n]s",msg_s);
//			 puts(msg_s);
	                if (send(new_fd,msg_s,200,0)<0)
        	                printf ("msg not sent\n");

		}
	}
	else
	{
		char msgr[200];
		while(1)
		{
//			char msgr[200];
			if (recv(new_fd,msgr,200,0)<0)
                	{
			       	perror ("recv error:");
				exit(1);
				//puts("\nkrishna");}
			}
			else
			{
				printf ("he/she :: %s\n",msgr);
			}
			if (!strcmp(msgr,"exit"))
			{
                             /*   exit(1);
                                close(sockfd);
                                if (x!=0)
                                        kill(x,SIGTERM);*/
				printf("other side logged off\n");
				goto end;
                        }
					//printf("\n he/she :: %s",msgr);
		}
	}
	end: ;
//	close(sockfd);
	puts("logging of chat\n");
	if (x!=0)
		kill(x,SIGTERM);
	close(sockfd);
	return 0;
}

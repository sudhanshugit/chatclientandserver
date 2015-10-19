#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include "ip_check.h"
#define SIZE 10
void talk1(int);
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
	int x = bind(sockfd,(struct sockaddr *)&my_addr, sizeof(struct sockaddr));
	if (x<0)
		{printf ("the binding failed\n");perror("bind :");}
	else
	{
		puts ("bind done\n");
	}
	if (listen(sockfd,SIZE)<0)
		printf ("the listening failed\n");
	puts("waiting for incoming connection...\n");
	int sin_size= sizeof(struct sockaddr_in);
	int new_fd[SIZE];
	int pid[SIZE];
	int i=1;
	while(i<SIZE)
	{
		printf("waiting for next incoming connection ....\n");
		if ((new_fd[i]=accept(sockfd,(struct sockaddr *)&their_addr,&sin_size))==-1)
		{
			perror ("not accepted");
			continue;
		}
		printf("server got connection from %d\n",inet_ntoa(their_addr.sin_addr));
		int flag=0;
		pid[i]=fork();
		if (!pid[i])
		{
			//if (i==1)
			{
				if(send(new_fd[i],"welcome to sudhanshu's chat server \nwait for other to connect\n",65,0)==-1)
					perror("send");
				talk1(new_fd[i]);
			}
		/*	else if (i==2)
			{
                                if(send(new_fd[i],"welcome to sudhanshu's chat server\n",40,0)==-1)
                                        perror("send");
				talk1(new_fd[i];
			}*/
		}
		i++;
		printf("%d %d\n",i,pid[i]);
		if (i>=SIZE) break;
	}
	//wait (pid[1]);
	//wait (pid[2]);
	return 0;
}

void talk1(int new_fd)
{
	int x;
	//x=fork();
	int fd_me,fd_u;
	char u_id[50];
	char me_id[50];
	recv(new_fd,me_id,50,0);
	puts(me_id);
	recv(new_fd,u_id,50,0);
	puts(u_id);
	char str_me[50]="./tmp/fifo_";
	char str_u[50]="./tmp/fifo_";
	strcat(str_me,me_id);
	puts(str_me);
	strcat(str_u,u_id);
	puts(str_u);
	mkfifo(str_me,0777);
	printf("%s fifo file created\n",str_me);
//	fd_me=open(str_me,O_WRONLY);
	//fd_u=open(str_u,O_RDONLY);
	x=fork();
	/****************************send part************************/
	if (x!=0)
	{
		while(1)
	        {
        	        char msg_r[200];

			{
				fd_me=open(str_me,O_WRONLY);
				if(recv(new_fd,msg_r,200,0)<0)
					perror("recv client1");
				write(fd_me,msg_r,200);
				/*if (send(new_fd2,msg_s,200,0)<0)
                                	perror("send client2");*/
			}



		}
	}
/***********************************recv part*********************************/
	else
	{
		char msg_s[200];
		while(1)
		{
			fd_u=open(str_u,O_RDONLY);
			read(fd_u,msg_s,200);

			if (send(new_fd,msg_s,200,0)<0)
                	{
			       	perror ("send client1:");
				exit(1);

			}

			/*if (send(new_fd1,msgr,200,0)<0)
				perror("send client1");*/


		}//while ends
	}//else ends

}

/**************************************************************talk 2****************************************************************************
******************************************************************************************************************************************/


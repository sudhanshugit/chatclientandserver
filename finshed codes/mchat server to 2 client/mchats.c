#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
//#define MYPORT 3490
#include <stdlib.h>
#include <signal.h>
#include "ip_check.h"
void talk1(int,int);
void talk2(int,int);
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
	int new_fd[5];
	int pid[5];
/*	int fifo=mkfifo("/temp/temp_fifo1",0777);
		if (fifo == 0) {puts("error file opening\n");exit(1);}
	fifo=mkfifo("/temp/temp_fifo2",0777);
		if (fifo == 0) {puts("error file opening\n");exit(1);}
	int new_fd =accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
	if (new_fd<0)
		printf ("connection not accepted\n");
	puts("connection accepted\n");*/
	int i=1;
	while(i<3)
	{
//		sin_size =sizeof(struct sockaddr_in);
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
			//child process;
			if (i==1)
			{
				if(send(new_fd[i],"welcome to sudhanshu's chat server \nwait for other to connect\n",65,0)==-1)
					perror("send");
			}
			else if (i==2)
			{
                                if(send(new_fd[i],"welcome to sudhanshu's chat server\n",40,0)==-1)
                                        perror("send");
				talk1(new_fd[1],new_fd[2]);
			//	flag=1;
			}
			/*if (flag == 1)
			{
				talk2(new_fd[i]);
				flag=0;
			}*/
		}
		i++;
		if (i>5) break;
	}
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
//	x=fork();
	//talk(new_fd);
//	 end: ;
//      close(sockfd);
	/*char end[10];
	gets(end);
	if (!strcmp(end,"exit"))
	{
        	puts("logging of chat\n");
  //      if (x!=0)
    //            kill(x,SIGTERM);
        	close(sockfd);
		close(new_fd[1]);
		close(new_fd[2]);
		exit(1);
	}*/
	wait (pid[1]);
	wait (pid[2]);
	return 0;
}
//	while(1){
void talk1(int new_fd1,int new_fd2)
{
	int x;
	x=fork();
	int fd1,fd2;
	/****************************send part************************/
	if (x!=0)
	{
		while(1)
	        {
        	        char msg_s[200];
//			printf ("me ::");
			//gets(msg_s);
//			printf ("\n");
			//if (!strcmp(msg_s,"exit"))
			{
				//fd=open("/temp/fifo_temp1",O_RDONLY);
				//fread(msg_s,200,1,fifo_temp1);
				/*exit(1);
				 close(sockfd);
				 if (x!=0)
                			kill(x,SIGTERM);*/
				if(recv(new_fd1,msg_s,200,0)<0)
					perror("recv client1");
		//		puts(msg_s);
				if (send(new_fd2,msg_s,200,0)<0)
                                	perror("send client2");

				//goto end;
			}

//                	scanf("%[^\n]s",msg_s);
//			 puts(msg_s);
	                //if (send(new_fd,msg_s,200,0)<0)
        	          //      printf ("msg not sent\n");

		}
	}
/***********************************recv part*********************************/
	else
	{
		char msgr[200];
		while(1)
		{
//			char msgr[200];
			//puts("asdfdf");
			if (recv(new_fd2,msgr,200,0)<0)
                	{
			       	perror ("recv client1:");
				exit(1);
				//puts("\nkrishna");}
			}
		//	puts(msgr);
			if (send(new_fd1,msgr,200,0)<0)
				perror("send client1");
			/*else
			{
				printf ("he/she :: %s\n",msgr);
			}
			//if (!strcmp(msgr,"exit"))
			{
                             /*   exit(1);
                                close(sockfd);
                                if (x!=0)
                                        kill(x,SIGTERM);*/
			//	printf("other side logged off\n");
			//	goto end;
                        
			//goto end;		//printf("\n he/she :: %s",msgr);
		}//while ends
	}//else ends
	//end: ;
}
/*	end: ;
//	close(sockfd);
	puts("logging of chat\n");
	if (x!=0)
		kill(x,SIGTERM);
	close(sockfd);
	return 0;*/
/**************************************************************talk 2****************************************************************************
******************************************************************************************************************************************/
void talk2(int new_fd,int new_fd2)
{
        int x;
        x=fork();
        /****************************send part************************/
        if (x!=0)
        {
                while(1)
                {
                        char msg_s[200];
//                      printf ("me ::");
                        gets(msg_s);
//                      printf ("\n");
                        //if (!strcmp(msg_s,"exit"))
                        {
                                /*exit(1);
                                 close(sockfd);
                                 if (x!=0)
                                        kill(x,SIGTERM);*/
                                if (send(new_fd,msg_s,200,0)<0)
                                printf ("msg not sent\n");

         //                       goto end;
                        }

//                      scanf("%[^\n]s",msg_s);
//                       puts(msg_s);
                        if (send(new_fd,msg_s,200,0)<0)
                                printf ("msg not sent\n");

                            //    goto end;
                        

//                      scanf("%[^\n]s",msg_s);
//                       puts(msg_s);
                        //if (send(new_fd,msg_s,200,0)<0)
                          //      printf ("msg not sent\n");

                }
        }
/***********************************recv part*********************************/
        else
        {
                char msgr[200];
                while(1)
                {
//                      char msgr[200];
                        //puts("asdfdf");
                        if (recv(new_fd,msgr,200,0)<0)
                        {
                                perror ("recv error:");
                                exit(1);
                                //puts("\nkrishna");}
                        }
 //                       else
   //                     {

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
  //                              goto end;
                        }
                        //goto end;             //printf("\n he/she :: %s",msgr);
                }//while ends
        //else ends
        //end: ;
}}

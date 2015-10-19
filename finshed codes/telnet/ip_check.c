#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
int ip_check(int argc, char *ip ,char *port)
{
	puts(ip);
	int fl=1;
	if (argc < 2)
		printf ("error :: enter two arguments ip address and port no.\n");
	if (strlen(ip)>=17)
			{printf ("improper length of ip\n");fl--;}
	int cnt=1;
	char *re;
	while (cnt !=5 || re == NULL)
	{
		if (cnt==1)
			re=strtok(ip,".");
		else
			re=strtok(NULL,".");
		int x = atoi(re);
		if (x>=0&&x<=255)
			fl++;
		else
			fl=0;
		cnt++;
	}

	int flag=0;
	if(fl!=5)
		{printf ("error :: enter valid ip\n");flag=0;}
	else {puts("ip correct");flag=1;}
	if ((atoi(port)>2000 && atoi(port)<65535))
		{printf ("valid port no.\n");flag=1;}
	else
		{puts("error :: enter valid port no.\n");flag=0;}
	return (flag);
}

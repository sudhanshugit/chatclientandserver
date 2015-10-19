#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
//#include <sys>
#include <netinet/in.h>
int ip_check(int argc, char *ip ,char *port)
{
	int fl=1;
	if (argc < 2)
		printf ("error :: enter two arguments ip address and port no.\n");
	if (strlen(ip)>=17)
			{printf ("improper length of ip\n");exit(1);}
	int cnt=1;
//	char *cmp;
	char *re;//=strtok(ip,".");
	while (cnt !=5 || re == NULL)
	{
		if (cnt==1)
			re=strtok(ip,"."); 
			if (re==NULL) goto end;
		else
			re=strtok(NULL,".");
			if (re==NULL) goto end;
		int x = atoi(re);
//		printf ("atoi = %d:: re=%s\n",x,re);
		if (x>=0&&x<=255)
			fl++;
		else
			fl=0;
//		re = strtok(0,".");
//		puts("hgkj");
//		ip++;
		cnt++;
	}
	end: ;
	printf("fl=%d\n",fl);
	//if (!fl)
	//end : ;
	if(fl!=4)
		{printf ("error :: enter valid ip\n");exit(1);}
	else puts("ip correct");
	printf ("%d\n",atoi(port));
	if ((atoi(port)>2000 && atoi(port)<65535))
		printf ("valid port no.\n");
	else
		{puts("error :: enter valid port no.\n");exit(1);}
	//x=atoi(ip);
	//puts(argv[1]);
	//puts(argv[2]);
	//puts(argv[3]);
	if (fl==4)
		return (1);
	else
		exit(1);
}

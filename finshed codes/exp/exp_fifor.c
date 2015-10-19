#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
	char str[500],str1[500];
	mkfifo("./sud/kumar",0777);
	int fd=open("./sud/sudha",O_RDONLY);
	int fd1=open("./sud/kumar",O_WRONLY);
	if (fd<0)
	{perror("file");exit(1);}
	while(strcmp(str,"exit"))
	{
		gets(str1);
		write(fd1,str1,500);
		read(fd,str,500);
		puts(str);
	}
	return 0;
}

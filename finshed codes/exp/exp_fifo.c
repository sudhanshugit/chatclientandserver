#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
	mkfifo("./sud/sudha",0777);
//	int x=fork();
	//if (x!=0)
	int fd=open("./sud/sudha",O_WRONLY);
	int fd1=open("./sud/kumar",O_RDONLY);
	char data[500],data1[500];
	gets(data);
	//int data_length=strlen()
	while(strcmp(data,"exit"))
	{
		gets(data);
		//int fd=open("./sud","r");
		write(fd,data,500);
		read(fd1,data1,500);
		puts(data1);
	//	close(fd);
	}
	close(fd);
	return 0;
}


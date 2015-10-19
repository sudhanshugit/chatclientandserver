/*this experiment is for checking entries in a directory so that we can 
check that a person is online or not by checking the fifo file entry
of his name and accordingly we will send a signal to the other client*/
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
int main()
{
	//struct stat dir;
	//struct stat *content;
	DIR* dir;
	struct dirent* entry;
	dir=opendir("./");
	while((entry = readdir(dir))!=NULL)
	{
		puts(entry->d_name);
	}
	return 0;
}

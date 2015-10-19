#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
int main()
{
	int i,k;
	pid_t j[10];
	for (i=1;i<=10;i++) {j[i]=10; printf ("%d %d \n",i,j[i]);}
//	puts("adf");
	i=1;
	for (i=1;i<=10;i++)
	{
		puts("before fork\n");
//		j[i]=fork();
		puts("jst aftr frk\n");
		printf ("child pid= %d\n",j[i]);
		//j[i]=fork();
		if (j[i]==0) // child
		{
			puts("child\n");
		}
		else
		{
			j[i]=fork();
			puts("after fork\n");
			//printf("i=%d pid= %d",i-1,j[i-1]);
			//j[i]=fork();
		}
		/*else
		{
			while(1);
		}*/
	}
	return 0;
}

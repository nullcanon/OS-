#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main()
{
	int ret = open("./mypipe",O_WRONLY);
	if(ret < 0)
	{
		perror("open");
		exit(1);
	}
	char buf[1024] = {0};
	while(1)
	{
		printf(">:");
		fflush(stdout);
		ssize_t read_size = read(0,buf,sizeof(buf)-1);
		if(read_size > 0)
		{
			buf[read_size] = '\0';
			write(ret,buf,strlen(buf));
		}
		else 
		{
			perror("read");
			continue;
		}
	}
	return 0;
}

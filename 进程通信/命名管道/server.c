#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdio.h>


int main()
{
	int ret = open("./mypipe",O_RDONLY);
	if(ret < 0)
	{
		perror("open");
		exit(1);
	}
	char buf[1024] = {0};
	while(1)
	{
		ssize_t read_size = read(ret,buf,sizeof(buf)-1);
		if(read_size < 0)
		{
			perror("read");
			continue;
		}
		else if(read_size == 0)
		{
			printf("一个客户端退出\n");
			break;
		}
		else
		{
			buf[read_size] = '\0';
			printf("[client]:");
			fflush(stdout);
			write(1,buf,strlen(buf));
		}

	}
	close(ret);
	return 0;
}


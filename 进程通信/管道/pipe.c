
#include<stdio.h>
#include<string.h>
#include<unistd.h>

/*管道操作：管道其实是操作系统提供的一段内存
 * 管道操作必须是有亲缘关系的进程
 *int pipe(int fd[2])--创建无名管道
 *fd:文件描述符数组，fd[0]--读端，fd[1]--写端
 * 成功返回0，失败返回错误代码
 */
void Test1()
{
	int fd[2];
	int ret = pipe(fd);
	if(ret <  0)
	{
		perror("pipe");
		return;
	}

	//通过fork创建子进程，父进程从管道一端写，子进程从管道读
	int pid = fork();

	const char* str = "hello\n";
	if(pid > 0)
	{
		//father write
		close(fd[0]);
		write(fd[1],str,strlen(str));
		close(fd[1]);
		printf("father:%d\n",getpid());
	}
	else if(pid == 0)
	{
		//child read
		close(fd[1]);
		char buf[1024] = {0};
		read(fd[0],buf,sizeof(buf)-1);//-1操作是为了给'\0'预留位置
		close(fd[0]);
		printf("child:%d ,%s\n",getpid(),buf);

	}
	else
		perror("fork");
	sleep(1);
}

int main()
{
	Test1();
	return 0;
}

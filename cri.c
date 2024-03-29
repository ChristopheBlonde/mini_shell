#include <unistd.h>
#include <fcntl.h>

int main (int argc, char **argv, char **envp)
{
	char *str[] = {"|",NULL, "-l", NULL};

	int fd = open("./test.txt", O_CREAT, 0777);

	execve("/bin/ls", str + 1, envp);
	


	return 0;
}
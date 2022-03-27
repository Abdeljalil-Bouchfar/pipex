#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
int main()
{
	char *argv[] = {"ls", "-l", NULL};
	execve("/bin/ls", argv, NULL);
}
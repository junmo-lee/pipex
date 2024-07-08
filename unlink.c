#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	printf("%d\n", unlink(".here_doc"));
	perror("unlink error!");
}
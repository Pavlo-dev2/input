#include "input.h"
#include <stdio.h>
#include <unistd.h>
#include <linux/input.h>
#include "linkedlistlib.h"

int main()
{
	int fd = retfd(0, 2);
	printf("FD: %d\n", fd);
	printf("ifev: %d\n", ifevent(fd, KEY_W, 2, -1));
	close(fd);
}

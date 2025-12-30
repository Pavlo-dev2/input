#include "input.h"
#include <stdio.h>
#include <unistd.h>
#include <linux/input.h>
#include "linkedlistlib.h"

int main()
{
	int fd = retfd(1, 2);
	printf("FD: %d\n", fd);
	/*
	printf("ifev: %d\n", ifevent(fd, KEY_W, 2, -1));
	*/

	int ev1[] = {KEY_W, 1};
	int ev2[] = {KEY_D, 1};
	int ev3[] = {KEY_S, 1};
	int ev4[] = {KEY_A, 1};
	int* events[] = {ev1, ev2, ev3, ev4};

	int *retvel = ifevents(fd, events, 4, 0, 2);

	printf("RETVEL: %p\n{%d, %d}\n", retvel, retvel[0], retvel[1]);

	close(fd);
}

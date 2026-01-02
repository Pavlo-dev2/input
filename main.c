#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>
#include "timing.h"

int main()
{
	int fd = retfd(1, 2);
	printf("FD: %d\n", fd);
	
	//ifevent test;
	/*
	printf("ifev: %d\n", ifevent(fd, KEY_W, 2, -1));
	*/

	//ifevents test;
	/*
	int ev1[] = {KEY_W, 0};
	int ev2[] = {KEY_D, 1};
	int ev3[] = {KEY_S, 0};
	int ev4[] = {KEY_A, 1};
	int* events[] = {ev1, ev2, ev3, ev4};

	int *retvel = ifevents(fd, events, 4, 0, 2);

	printf("RETVEL: %p\n{%d, %d}\n", retvel, retvel[0], retvel[1]);
	free(retvel);
	*/

	//ifeventscode test;
	/*
	int events[] = {KEY_W, KEY_D, KEY_S, KEY_A};
	printf("Ifeventscode: %d\n", ifeventscode(fd, events, 4, 1, 2));
	*/
	
	//ifeventsvalue test
	/*
	sleepsec(1);
	printf("Go\n");
	printf("Ifeventscode: %d\n", ifeventsvalue(fd, 1, 0, 4));
	*/
	
	//ifanyevent test
	int *retvel = ifanyevent(fd, 1, 3);
	printf("RETVEL: %p\n{%d, %d}\n", retvel, retvel[0], retvel[1]);
	free(retvel);

	close(fd);
}

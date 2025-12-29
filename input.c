#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <errno.h>
#include <sys/select.h>
#include "timing.h"
#include "linkedlistlib.h"

int retfd(char type, char num);
//returns file deckriptor;
//type - type of the deckriptor, 0: Blocking, 1: Nonblocking;
//num - number of the /dev/input/event* file;

int ifevent(int fd, int keynum, char evvel, int time);
//returns 1 if event with number keynum and type evtype hapend, else 0;
//waits time second if nonblocking;

int* ifevents(int fd, listelement* events, char type, int time);
//returns event([number, type])if event from events hapend, else NULL;
//type - type of shering, 0 for first event, 1 for last;
//waits time seconds if nonblocking;
//if events == NULL reacts to all of events;

int retfd(char type, char num)
{
	char addres[] = "/dev/input/event ";//16 - possion of the file number;
	addres[16] = '0' + num;
	int fd = -1;
	switch (type)
	{
		case 0:
			fd = open(addres, O_RDONLY);
			break;
		case 1:
			fd = open(addres, O_RDONLY | O_NONBLOCK);
			break;
	}
	return fd;
}

int ifevent(int fd, int keynum, char evval, int time)
{
	struct input_event ev;
	long double bt = rettime();//begining time;
	while (timediff(bt, rettime()) < time || time == -1)
	{
		read(fd, &ev, sizeof(ev));
		//printf("Type: %d Code: %d Value: %d\n", ev.type == EV_KEY, (int) ev.code, (int) ev.value);
		if (ev.type == EV_KEY && ev.code == keynum && (ev.value == evval || evval == 2))
		{
			return 1;
		}

	}
	return 0;

}

int* ifevents(int fd, listelement* events, char type, int time)
{
	struct input_event ev;
	
	if (time == -1 && type != 0)
	{
		return NULL;//check
	}

	int last_event[2] = {-1, -1};//list with events that alredy hapend;

	int *nev = calloc(2, sizeof(int));
	
	long double bt = rettime();//begining time;
	while (timediff(bt, rettime()) < time || time == -1)
	{
		read(fd, &ev, sizeof(ev));
		nev[0] = ev.code;
		nev[1] = ev.value;
		if (ifinlist(events, nev, 'i', 2))
		{
			if (type == 1)
			{
				last_event[0] = nev[0];
				last_event[1] = nev[1];
			}
			else if (type == 0)
			{
				return nev;
			}
		}
	}

}

/*
static int fd = -1;//file deckriptor
static char lastdr = 'u';//last direction

char input(float st)
{
	struct input_event ev;//event
	char dr = 0;//new ditection
	
	//open file deckriptor
	if (fd == -1)
	{
		fd = open(ADDRES, O_RDONLY | O_NONBLOCK);
	}

	long double bt = rettime();//begining time

	//wait on input as long as you have time
	//while ((st - (td = (clock()/CLOCKS_PER_SEC) - at)* 1000000) > 0)//TODO
	while (timediff(bt, rettime()) < st)
	{
		//printf("Actual time: %ld\nBegining time: %f\nTime: %f\n", clock()/CLOCKS_PER_SEC, bt, st);
		read(fd, &ev, sizeof(ev));
		if (ev.type == EV_KEY)
		{
			switch (ev.code)
			{
				case KEY_W:
					if (lastdr != 'd')
						dr = 'u'; break;
				case KEY_D:
					if (lastdr != 'l')
						dr = 'r'; break;
				case KEY_S:
					if (lastdr != 'u')
						dr = 'd'; break;
				case KEY_A:
					if (lastdr != 'r')
						dr = 'l'; break;
				case KEY_E:
					dr = 'E'; break;
			}
			//break;
		}
		//printf("ST: %.0f\n", st);
		sleepsec(st*0.001);
	}

	if (dr != 0)
	{
		lastdr = dr;
	}

	return lastdr;
}
*/

#ifndef INPUT_H
#define INPUT_H

int retfd(char type, char num);
//returns file deckriptor;
//type - type of the deckriptor, 0: Blocking, 1: Nonblocking;
//num - number of the /dev/input/event* file;

int ifevent(int fd, int keynum, char evtype, int time);
//returns 1 if event with number keynum and type evtype hapend, else 0;
//waits time second if nonblocking;

int* ifevents(int fd, linkedlist* events, char type, int time);
//returns event([number, type])if event from events hapend, else NULL;
//type - type of shering, 0 for first event, 1 for last, 2 for that with hepend most time;
//waits time seconds if nonblocking;
//if events == NULL reacts to all of events;

#endif 

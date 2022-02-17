#include "stdio.h"

#define MAX_CHARACTER 5

struct Room {
	char* name;
	struct Room *North;
	struct Room *South;
	struct Room *East;
	struct Room *West;
	struct Item *Itemlist;
	char *character[MAX_CHARACTER];

};

extern void initializerooms();
extern struct Room *room(int i);

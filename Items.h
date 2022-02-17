#include "stdio.h"

struct Item {
	char* name;
	struct Item *next;
};


extern void initializeitems();
extern struct Item* item(int i);

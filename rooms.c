#include "rooms.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

//initializes rooms
struct Room bedroom = (struct Room) {"bedroom\0", NULL, NULL, NULL, NULL, NULL, {"", "", "", "", ""}};
struct Room bathroom = (struct Room) {"bathroom\0", NULL, NULL, NULL, NULL, NULL, {"", "", "", "", ""}};
struct Room balcony = (struct Room) {"balcony\0", NULL, NULL, NULL, NULL, NULL, {"", "", "", "", ""}};
struct Room kitchen = (struct Room) {"kitchen\0", NULL, NULL, NULL, NULL, NULL, {"", "", "", "", ""}};
struct Room living = (struct Room) {"living room\0", NULL, NULL, NULL, NULL, NULL, {"", "", "", "", ""}};
struct Room pool = (struct Room) {"pool\0", NULL, NULL, NULL, NULL, NULL, {"", "", "", "", ""}};
struct Room guest = (struct Room) {"guest\0", NULL, NULL, NULL, NULL, NULL, {"", "", "", "", ""}};
struct Room dining = (struct Room) {"dining\0", NULL, NULL, NULL, NULL, NULL, {"", "", "", "", ""}};
struct Room closet = (struct Room) {"closet\0", NULL, NULL, NULL, NULL, NULL, {"", "", "", "", ""}};

//rooms pointers
struct Room *r1;
struct Room *r2;
struct Room *r3;
struct Room *r4;
struct Room *r5;
struct Room *r6; 
struct Room *r7;
struct Room *r8;
struct Room *r9;

//list of rooms
struct Room *rooms[] = {&bedroom, &bathroom, &balcony, &kitchen, &living, &pool, &guest, &dining, &closet};
int length = 9;

//swaps position of two rooms in list
void swap(struct Room **a, struct Room **b){

 struct Room *temp = *a;
 *a = *b;
 *b = temp;

}

//randomizes order of rooms in list
void randomize(){

  srand(time(NULL));

  for (int i = 8; i > 0; i--){
     int j = rand() % (i+1);
     swap(&rooms[i], &rooms[j]);
  }

}

//initializes position of rooms
void initializerooms(){

	randomize();

	r1 = rooms[0];
        r1->East = rooms[1];
        r1->South = rooms[2];

        r2 = r1->East;
        r2->West = r1;
        r2->East = rooms[3];
        r2->South = rooms[4];

	r3 = r2->East;
	r3->West = r2;
        r3->South = rooms[5];

	r4 = r3->South;
	r4->North = r3;
	r4->West = r2->South;
	r4->South = rooms[6];

	r5 = r4->West;
	r5->East = r4;
	r5->North = r2;
	r5->West = r1->South;
	r5->South = rooms[7];

	r6 = r1->South;
	r6->North = r1;
	r6->East = r5;
	r6->South = rooms[8];

	r7 = r6->South;
	r7->North = r6;
	r7->East = r5->South;

	r8 = r7->East;
	r8->West = r7;
	r8->North = r5;
	r8->East = r4->South;

	r9 = r4->South;
	r9->North = r4;
	r9->West = r8;

}

//returns room given integer
struct Room *room(int i){

  struct Room *r;

  switch(i){

    case 0: r = r1; break;
    case 1: r = r2; break;
    case 2: r = r3; break;
    case 3: r = r4; break;
    case 4: r = r5; break;
    case 5: r = r6; break;
    case 6: r = r7; break;
    case 7: r = r8; break;
    case 8: r = r9; break;
    default: r = NULL;

  }

  return r;

}

#include "Items.h"
#include "rooms.h"
#include "stdio.h"
#include "stdlib.h"

//initalizes items
struct Item iron = {"curling iron\0", NULL};
struct Item mirror = {"pocket mirror\0", NULL};
struct Item pan = {"frying pan\0", NULL};
struct Item noodle = {"pool noodle\0", NULL};
struct Item candle = {"candle\0", NULL};
struct Item heels = {"high heels\0", NULL};

//adds item to room's item list
void setlocation(struct Room *r, struct Item *i){

  r->Itemlist = i;

}

//sets location of each item
void initializeitems(){

  setlocation(room(0), &iron);
  setlocation(room(1), &mirror);
  setlocation(room(2), &pan);
  setlocation(room(3), &noodle);
  setlocation(room(4), &candle);
  setlocation(room(5), &heels);

}

//returns item given an integer
struct Item *item(int i){

 struct Item *list[6] = {&iron, &mirror, &pan, &noodle, &candle, &heels};

 return list[i];

}

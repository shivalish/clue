#include "avatar.h"
#include "Items.h"
#include "rooms.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

//initialize objects
struct Avatar avatar = {NULL, NULL}; //main user
char *characters[5] = {"Skipper\0", "Ken\0", "Ryan\0", "Racquelle\0", "Teresa\0"}; //game characters
char *answer[3]; //final solution
int cluecounter = 0; //tracks number of clues so far
int win = 0; //tracks if won game

//finds item in room or inventory
int findItem() {

 int found = 0; //0 item not found, 1 found
 struct Item *rptr = avatar.location->Itemlist; //pointer to room list

 //searches for item in room
 while (rptr != NULL) {
   
   if (strncmp(rptr->name, answer[1], strlen(answer[1])) == 0) {
      found = 1;
      break;
   }

   rptr = rptr->next;

  }

 if (found == 0) {

   rptr = avatar.inventory;

   //searches for item in inventory
   while (rptr != NULL) {
   
     if (strncmp(rptr->name, answer[1], strlen(answer[1])) == 0) {
        found = 1;
        break;
     }

     rptr = rptr->next;

   }

 }

 return found;

}
//initializes avatar location
void initializeavatar(){
  avatar.location = room(rand() % 9);
}
//initializes solution
void initializeanswer(){

  answer[0] = room(rand()%9)->name;
  answer[1] = item(rand()%6)->name;
  answer[2] = characters[rand() % 5];

}
//initializes placement of characters
void initializecharacters(){

 room(3)->character[0] = characters[0];
 room(4)->character[0] = characters[1];
 room(5)->character[0] = characters[2];
 room(6)->character[0] = characters[3];
 room(7)->character[0] = characters[4];

}
//lists all rooms, characters, items
void list(){

  printf("The list of characters are: Skipper, Racquelle, Ryan, Teresa, and Ken\n");
  printf("The possible items are: a frying pan, curling iron, pocket mirror, candle, and pool noodle\n");
  printf("The rooms are: bedroom, living room, dining room, balcony, kitchen, closet, pool, and guest bedroom\n");
  printf("Looks like Barbie doesn't invite you here often...\n");
}
//lists commands
void help() {

  printf("go : go in a direction\n");
  printf("take : take an item from the room\n");
  printf("drop : drop an item from inventory\n");
  printf("inventory : check inventory\n");
  printf("list : lists items, characters, and rooms\n");
  printf("look : gives the room and the characters and items in the room\n");
  printf("clue : lets you guess\n");
  printf("quit : quits the game\n");

}
//lists items
void listItems(struct Item *ptr){

  while (ptr != NULL) {
    printf("%s ", ptr->name);
    ptr = ptr->next;
  }

}

//moves character
void movecharacter(char *name) {

   int moved = 0; //0, not moved, 1 successfully moved

   for (int i = 0; i < 9; i++) {

     struct Room *r = room(i); //room

      //finds character in room
     for (int j = 0; j < 5; j++) {
        
        if (strncmp(r->character[j], name, strlen(name)) == 0) {
           
            //removes character from room
            char *c = r->character[j];
            r->character[j] = "";
            
            //adds character to current room
            for (int x = 0; x < 5; x++) {
               if (strlen(avatar.location->character[x]) == 0) {
                   avatar.location->character[x] = c;
                   moved = 1;
                   break;
               }

            } 

        }
            

      }

       if (moved == 1) { break; }

   }

}

//room, room in each direction, characters in the room, items in the room
void look(){

 struct Room *r = avatar.location;

 printf("You are in the %s. ", r->name);

 if (r->North != NULL) {
   printf("The %s is to the North. ", r->North->name);
 }

 if (r->South != NULL) {
   printf("The %s is to the South. ", r->South->name);
 }

 if (r->East != NULL) {
   printf("The %s is to the East. ", r->East->name);
 }

 if (r->West != NULL) {
   printf("The %s is to the West. ", r->West->name);
 }

 printf("\nThe characters in the room are ");
 int num = 0;

 for (int i = 0; i < 5; i++){
    if (strlen(r->character[i]) != 0){
       num = 1;
       printf("%s.", r->character[i]);
    }
 }

  if (num == 0) {
   printf("none.");
  }

  printf("\nThe items in the room are: ");
  listItems(r->Itemlist);

  printf("\n");

}
//go in a direction
void go(){

  char *input; //user input
  size_t bufsize = 0;

  input = (char *)malloc(bufsize * sizeof(char));

  printf("Which direction would you like to go?\n");
  getline(&input, &bufsize, stdin);

  int valid = 1; //1 valid direction, 0 invalid direction

  if (strncmp("north", input, strlen("north")) == 0){

     if (avatar.location->North == NULL) {
         valid = 0;
     } else {
         avatar.location = avatar.location->North;
         look();
     }

  } else if (strncmp("south", input, strlen("south")) == 0) {

      if (avatar.location->South == NULL) {
          valid = 0;
      } else {
          avatar.location = avatar.location->South;
          look();
      }

   } else if (strncmp("east", input, strlen("east")) == 0) {

       if (avatar.location->East == NULL) {
           valid = 0;
       } else {
            avatar.location = avatar.location->East;
            look();
       }

   } else if (strncmp("west", input, strlen("west")) == 0) {

       if (avatar.location->West == NULL) {
          valid = 0;
       } else {
          avatar.location = avatar.location->West;
          look();
       }

    } else {
         valid = 0;
    }

  if (valid == 0) {

   char tryagain;

   printf("There is no room in that direction. Do you want to try again? y/n\n");
   scanf(" %c", &tryagain);
   getchar();
     
   if (tryagain == 'y'){
     go();
   }

 }

}

//removes item from room and adds to inventory
void removeitemfromroom(struct Item *i, struct Item *list) {

  if (list == i) {
     avatar.location->Itemlist = avatar.location->Itemlist->next;
     i->next = avatar.inventory;
     avatar.inventory = i;
  } else {

       while (list->next != NULL && list->next != i) {
          list = list->next;
       }

       list->next = list->next->next;
       i->next = avatar.inventory;
       avatar.inventory = i;
  }


}

//take an item
void take(){

  char *input;
  size_t bufsize = 0;

  input = (char *)malloc(bufsize * sizeof(char));

  printf("Which item would you like to take?\n");
  getline(&input, &bufsize, stdin);

  struct Item *i = avatar.location->Itemlist;

  //find item in room
  while (i != NULL){
    if (strncmp(i->name, input, strlen(i->name)) == 0){
      break;
    }
    i = i->next;
  }

  if (i == NULL) {

    char tryagain;

    printf("Item not found. Do you want to take another item? y/n\n");
    scanf(" %c", &tryagain);
    getchar();
     
    if (tryagain == 'y'){
      take();
    }

   } else {
         removeitemfromroom(i, avatar.location->Itemlist);
         inventory();
         printf("The %s has been taken out of room and put into inventory\n", i->name);
   }

}

//removes item from inventory and adds to room item list
void removeitemfrominventory(struct Item *i, struct Item *list){

  if (i == list) {
    avatar.inventory = avatar.inventory->next;
    i->next = avatar.location->Itemlist;
    avatar.location->Itemlist = i;
  } else {

    while (list->next != NULL && list->next != i) {
        list = list->next;
    }

    list->next = list->next->next;
    i->next = avatar.location->Itemlist;
    avatar.location->Itemlist = i;

  }



}

//drops an item from inventory
void drop(){

    char *input;
    size_t bufsize = 0;

    input = (char *)malloc(bufsize * sizeof(char));

    printf("Which item would you like to drop?\n");
    getline(&input, &bufsize, stdin);

    struct Item *i = avatar.inventory;

    //finds item in inventory
    while (i != NULL){
      if (strncmp(i->name, input, strlen(i->name)) == 0){
      break;
    }
      i = i->next;
    }

    if (i == NULL) {

      char tryagain;

      printf("Item not found. Do you want to drop another item? y/n\n");
      scanf(" %c", &tryagain);
      getchar();
     
      if (tryagain == 'y'){
        drop();
      }

     } else {
	 removeitemfrominventory(i, avatar.inventory);
         printf("The %s has been taken out of inventory and put into the room\n", i->name);
     }


}

//list items in inventory
void inventory(){

   printf("The items in your inventory: ");
   listItems(avatar.inventory);
   printf("\n");

}

//allows user to guess character and outputs matches + determines
//if user won, lost, or neither. updates cluecounter accordingly
void clue(){

  char *input;
  size_t bufsize = 0;

  input = (char *)malloc(bufsize * sizeof(char));

  printf("Which character would you like to guess?\n");
  getline(&input, &bufsize, stdin);
  input[strlen(input) - 1] = '\0';

  int valid = 0; //0 invalid character, 1 valid character

  //finds character in character list
  for (int i = 0; i < 5; i++) {
     if (strncmp(input, characters[i], strlen(characters[i])) == 0){
        valid = 1;
        break;
     }
   }

  if (valid == 0) {

    char tryagain;

    printf("There's no person named that. This is the Barbie dreamhouse! Do you want to guess again? y/n\n");
    scanf(" %c", &tryagain);
    getchar();
     
    if (tryagain == 'y'){
      clue();
    }

  } else {

    movecharacter(input); //moves character to current room
    int matches = 0; //number of matches from guess to answer
    
    if (strncmp(input, answer[2], strlen(input)) == 0) {
       printf("Character Match\n");
       matches = matches + 1;
    }

    if (strncmp(avatar.location->name, answer[0], strlen(answer[0])) == 0) {
       printf("Room Match\n");
       matches = matches + 1;
    }

    if (findItem() == 1) {
      printf("Item Match\n");
      matches = matches + 1;
    }

    if (matches < 3 && cluecounter < 10) {
       cluecounter = cluecounter + 1; //some matches
       printf("\nNot quite! You have %i more guesses to avenge Barbie and appease Taffy's soul\n", 10-cluecounter);
    } else if (matches == 3 && cluecounter <= 10) {
       cluecounter = cluecounter + 1;
       win = 1; //won
       printf("\nYOU DID IT! YOU SOLVED THE MURDER!! Barbie thanks you for your service. Now get out of her dream house");
    } else if (cluecounter == 10) { //lost
       printf("\nYou have run out of guesses :( Barbie weeps knowing the murderer remains in her house, she kicks you out. Sorry\n");
  }

}

}

int main(){

   srand(time(NULL)); //randomize

   //initialize rooms, items, avatar, answer, and characters
   initializerooms();
   initializeitems();
   initializeavatar();
   initializeanswer();
   initializecharacters();
 
   printf("Welcome to Barbie Dream house! I know you are here to party in the fabulous world of Barbie but unfortunately,\n");
   printf("the murder of Barbie's dog Taffy has caused panic in the house. Barbie needs you to solve the mystery.\n");
   printf("You must guess the place of murder, the item of choice, and the culprit correctly or else Barbie will take you\n");
   printf("off the cool girls list, so do your best!\n");
   printf("type help to see list of commands");

   look();
   printf("\n\n");

   char *input;
   size_t bufsize = 0;

   input = (char *)malloc(bufsize * sizeof(char));

   //repeats while 
   while (cluecounter < 10 && win == 0) {

         getline(&input, &bufsize, stdin);
         input[strlen(input) - 1] = '\0';

         if (strcmp(input, "go") == 0) {
            go();
         } else if (strcmp(input, "take") == 0){
            take();
         } else if (strcmp(input, "drop") == 0) {
            drop();
         } else if (strcmp(input, "list") == 0) {
            list();
         } else if (strcmp(input, "look") == 0) {
            look();
         } else if (strcmp(input, "inventory") == 0) {
            inventory();
         } else if (strcmp(input, "clue") == 0) {
            clue();
         } else if (strcmp(input, "help") == 0) {
            help();
         } else if (strcmp(input, "quit") == 0) {
            exit(0);
         } else {
            printf("Command not recognized. Try again\n");
         }

    }

    free(input); //frees memory

}

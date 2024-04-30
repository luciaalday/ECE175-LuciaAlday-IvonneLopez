/********************************************************************
 * file: main.c
 * authors: Lucia Alday and Ivonne Lopez
 * course: ECE 175 Spring 2024
 * Game of Trains play and specifications:
 *** (gameplay and rules and how theyre implemented)
 *** (card struct)
 *** (deck struct)
 ********************************************************************/

#include <stdio.h>
#include <bool.h>
#define MAX_CARDS 84

typedef struct {
  int value;
  char action[15];
} card;

typedef struct {
  card hand[7];
} player;

void setup();
void round();
void cardsfile();
void shuffleDeck();

int main()
{
  int* p; //players 
  char choice;
  printf("Enter 'f' if to play you want to insert a file or enter 's' if you want to shuffle the deck: ");
  scanf("%c", &choice);

  if (choice == 'f') {
    char filename[]; 
    scanf("%s", &filename);
    cardsfile(filename);
  }
  else if (choice == 's'){
    shuffleDeck(); //random numbers 
  }
  printf("Enter the number of players: ");
  scanf("%d", p);
  bool winner = false;

  player player_array[*p];

  setup(p);

  while (winner = false){
    for(int i = 0; i <= *p; i++){
      round(p);
    }
  }
  

    return 0;
}

void setup(int *p){
  
}

void round() {

}
void cardsfile(char *filename){ //if user enters file 
  FILE *in;
  in = fopen(filename, "r");
  if (file == NULL){
    printf("The file does not exist");
    return -1;
  }
  else {
    index = 0;
    //scan cards from file
    while(index < MAX_CARDS && fscanf(file, "%d %s, &drawPile[index].value == 1) //scans card value and card action {
      index++;
      } //drawPile[index].action)==2
  }
}
  void shuffleDeck () { //if user chooses shuffle deck
      //random function
  }

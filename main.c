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
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
void shuffleDeck(card deck[]);
void createRandomDeck(card deck[]);
void printDeck(card deck[]);

int main()
{
  card deck[MAX_CARDS];
  int p; //players 
  char choice;
  printf("Enter 'f' if to play you want to insert a file or enter 's' if you want to shuffle the deck: ");
  scanf("%c", &choice);

  if (choice == 'f') {
    char filename[40]; 
    scanf("%s", &filename);
    cardsfile(filename);
  }
  else if (choice == 's') {
    createRandomDeck(deck);
  }
  else {
    printf("Invalid choice.");
    return -1;
  }

  shuffleDeck(deck); //calls function that shuffles deck
  printDeck(deck);
  
  printf("Enter the number of players: ");
  scanf("%d", p);
  bool winner = false;

  player player_array[4];

  setup(p);

  while (winner = false){
    for(int i = 0; i <= p; i++){
      round(p);
    }
  }
  

    return 0;
}

void setup(int p){
  return;
}

void round() {
  return;
}

void cardsfile(char *filename){ //if user enters file 
card drawPile[MAX_CARDS];
  FILE *in;
  in = fopen(filename, "r");
  if (in == NULL){
    printf("The file does not exist");
    return;
  }
  else {
    int index = 0;
    //scan cards from file
    while(index < MAX_CARDS && fscanf(in, "%d %s", &drawPile[index].value) == 1) { //scans card value and card action
      index++;
      } //drawPile[index].action)==2
  }
}

void createRandomDeck(card deck[]) { //if user chooses shuffle deck
    //random function
    char actions[8][15] =  {"swapAdjacent", "swapOver", "moveRight", "moveLeft", "removeLeft", "removeMiddle", "removeRight", "protect"};
    int random;
    for (int i = 0; i < MAX_CARDS; i++) {
      random = rand() % 8;
      card temp;
      temp.value = i;
      strcpy(temp.action, actions[random]);
      deck[i] = temp;
    }
}

void shuffleDeck(card deck[]) {
  for (int i = 0; i < MAX_CARDS; i++) {
    int temp = rand() % 84;
    card tempCard;
    tempCard = deck[i];
    deck[i] = deck[temp];
    deck[temp] = tempCard;
  }
  return;
}

void printDeck(card deck[]) {
  for (int i = 0; i < MAX_CARDS; i++) {
    printf("Value %d has action %s\n", deck[i].value, deck[i].action);
  }
}
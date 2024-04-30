/********************************************************************
 * file: main.c
 * authors: Lucia Alday and Ivonne Lopez
 * course: ECE 175 Spring 2024
 * Game of Trains play and specifications:
 *** (gameplay and rules and how theyre implemented)
 *** (card struct)
 *** (deck struct)

 * Implemented extra credit:
 *   Personalized name
 *   Play a full game (reshuffle deck)
 *   Additional players (asks user for and plays for 2-4 players)
 *   Graphics (?)
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
  bool used;
  bool protected;
} card;

typedef struct {
  card hand[7];
  char name[20]; 
} player;

void setup();
void cardsfile();
void shuffleDeck(card deck[]);
void createRandomDeck(card deck[]);
void printDeck(card deck[]);
void playRound(player player_array[], card deck[], card faceUp[]);
card drawCard(card deck[]);
void printHand(player p);
bool checkWin(player player_array[]);

/***********************************************************************
 * MAIN
 * 
 * creates deck
 ************************************************************************/
int main()
{
  card deck[MAX_CARDS];
  card faceUp[8];
  int SIZE; //players 
  char choice;
  printf("Enter 'f' if to play you want to insert a file or enter 's' if you want to shuffle the deck: ");
  scanf("%c", &choice);

  if (choice == 'f') {
    char filename[40]; 
    scanf("%s", filename);
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
  
  printf("Enter the number of players: ");
  scanf("%d", &SIZE);
  bool winner = false;

  player player_array[SIZE];

  setup(SIZE, player_array);

  while (winner = false){
    for(int i = 0; i <= SIZE; i++){
      playRound(player_array, deck, faceUp);
      if (checkWin(player_array)) {
        printf("Game has ended.");
        return 1;
      }
    }
  }
  

    return 0;
}

/***********************************************************************
 * SETUP
 ************************************************************************/
void setup(int SIZE, player player_array[]){
  return;
}

/***********************************************************************
 * ROUND
 ************************************************************************/
void playRound(player player_array[], card deck[], card  faceUp[]) {
  card drawn = drawCard(deck);
  return;
}

/***********************************************************************
 * CHECK WIN
 ************************************************************************/
bool checkWin(player player_array[]) {
  int length;
  bool winner = false;
  for (int i = 0; i < sizeof(player_array); i++) {
    length = 0;
    for (int j = 1; j < 7; j++) {
      if (player_array[i].hand[j].value > player_array[i].hand[j].value) {
        length++;
      }
    }
    if (length == 7) {
      printf("Congrats %s!\n", player_array[i].name);
      winner = true;
    }
  }
  return winner;
}

/***********************************************************************
 * PRINT HAND
 ************************************************************************/
void printHand(player p) {
  printf("%s:\n  oo o\nx||", p.name);
  for (int i = 0; i < 7; i++) {
    printf("  %d  |", p.hand[i].value);
  }
  printf("\n");
  for (int j = 0; j < 7; j++) {
    printf("");
  }
  printf("\n");

}

/***********************************************************************
 * CARDS FILE - creates deck from file
 ************************************************************************/
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

/***********************************************************************
 * CREATE RANDOM DECK
 ************************************************************************/
void createRandomDeck(card deck[]) { //if user chooses shuffle deck
    char actions[8][15] =  {"swapAdjacent", "swapOver", "moveRight", "moveLeft", "removeLeft", "removeMiddle", "removeRight", "protect"};
    int random;
    for (int i = 0; i < MAX_CARDS; i++) {
      random = rand() % 8;
      card temp;
      temp.used = false;
      temp.value = i;
      strcpy(temp.action, actions[random]);
      deck[i] = temp;
    }
}

/***********************************************************************
 * SHUFFLE DECK
 ************************************************************************/
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

/***********************************************************************
 * PRINT DECK - used to test functionality (not in gameplay)
 ************************************************************************/
void printAvailableDeck(card deck[]) {
  for (int i = 0; i < MAX_CARDS; i++) {
    if (!deck[i].used) {
      printf("Value %d has action %s\n", deck[i].value, deck[i].action);
    }
  }
}

/***********************************************************************
 * DRAW CARD
 ************************************************************************/
card drawCard(card deck[]) {
  int index = rand() % 84;
  card drawn = deck[index];
  bool needsReshuffle = true;
  for (int i = 0; i < MAX_CARDS; i++) {
    if (!deck[i].used) {
      needsReshuffle = false;
      break;
    }
  }
  if (needsReshuffle) {
    for (int j = 0; j < MAX_CARDS; j++) {
      deck[j].used = false;
    }
  }
  while (drawn.used) {
    index = rand() % 84;
    drawn = deck[index];
    deck[index].used = true;
  }
  return drawn;
}
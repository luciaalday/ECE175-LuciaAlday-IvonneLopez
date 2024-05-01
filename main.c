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
  bool used;
  char actionString[3];
} card;

typedef struct {
  card hand[7];
  char name[20]; 
} player;

void setup(int SIZE, player player_array[], card deck[]);
void quicksort(card cardsarray[], int low, int high);
void swap(card *a, card *b);
int partition(card cardsarray[], int low, int high);
void setup(int SIZE, player player_array[], card deck[]);
void quicksort(card cardsarray[], int low, int high);
void swap(card *a, card *b);
int partition(card cardsarray[], int low, int high);
void cardsfile();
void shuffleDeck(card deck[]);
void createRandomDeck(card deck[]);
void printAvailableDeck(card deck[]);
void playRound(player player_array[], card deck[], card faceUp[]);
card drawCard(card deck[]);
void printHand(player p);
bool checkWin(int SIZE, player player_array[]);

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
    cardsfile(filename); //calls function that scans file
    cardsfile(filename); //calls function that scans file
  }
  else if (choice == 's') {
    createRandomDeck(deck); //calls function  that generate random cards
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
  char tempName[30];

  char discard[5];
  fgets(discard, 5, stdin);


  for (int i = 0; i < SIZE; i++) {
    printf("Enter player %d name: ", i);
    fgets(player_array[i].name, 30, stdin);
  }
  /*delete this later*/
  printAvailableDeck(deck);

  player_array[0].hand[0] = drawCard(deck);
  player_array[0].hand[1] = drawCard(deck);
  player_array[0].hand[2] = drawCard(deck);
  player_array[0].hand[3] = drawCard(deck);
  player_array[0].hand[4] = drawCard(deck);
  player_array[0].hand[5] = drawCard(deck);
  player_array[0].hand[6] = drawCard(deck);

  printAvailableDeck(deck);

  printHand(player_array[0]);
  /*delete this later*/
  setup(SIZE, player_array, deck);

  while (winner == false){
    for(int i = 0; i <= SIZE; i++){
      playRound(player_array, deck, faceUp);
      if (checkWin(SIZE, player_array)) {
        printf("Game has ended.");
        return 1;
      }
    }
  }
    return 0;
}

/***********************************************************************
 * SETUP (int SIZE, plaer player_array[])
 ************************************************************************/
void setup(int SIZE, player player_array[], card deck[]){
  int playercards = 0;
  int i, j;
  
  
  for (i = 0; i <= SIZE ; i++){ //gives ecah player 7 cards
    for (j = 0; j <= 7; j++){
      card temp = drawCard(deck);
      player_array[i].hand[j] = temp;
    }
  }

  //while(){
  //player[i][j] = 0;
  for (i = 0; i <= SIZE; i++){
    quicksort(player_array[i].hand, 0, 6);
   } 
 }

void quicksort(card cardsarray[], int low, int high){ //quicksort function
  if(low < high) {
    int pivotindex = partition(cardsarray, low, high); //partition the array
    quicksort(cardsarray, low, pivotindex - 1); //sort cards before and after partition
    quicksort(cardsarray, pivotindex + 1, high);
  }
}
void swap(card *a, card *b){ //swaps the cards
  card temp = *a;
  *a = *b;
  *b = temp;
}
int partition(card cardsarray[], int low, int high){
  card pivot = cardsarray[high];
  int i = low - 1; //index of smaller card number

  for(int j = low; j < high; j++){
    if (cardsarray[j].value <= pivot.value) {
      i++;
      swap(&cardsarray[i], &cardsarray[j]);
    }
  }
swap(&cardsarray[i+1], &cardsarray[high]);
  return i + 1;
}

/***********************************************************************
 * ROUND (player player_array[], card deck[], card faceUp[])
 ************************************************************************/
void playRound(player player_array[], card deck[], card  faceUp[]) {
  return;
}

/***********************************************************************
 * CHECK WIN (player player_array[]) Returns boolean
 ************************************************************************/
bool checkWin(int SIZE, player player_array[]) {
  int length;
  bool winner = false;
  for (int i = 0; i < SIZE; i++) {
    length = 0;
    for (int j = 1; j < 7; j++) {
      if (player_array[i].hand[j].value > player_array[i].hand[j-1].value) {
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
 * PRINT HAND (player p)
 ************************************************************************/
void printHand(player p) {
  printf("%s:\n   OOo Oo o\n  O________________________________________________\n ||", p.name);
  for (int i = 0; i < 7; i++) {
    if (p.hand[i].value <10) {
      printf("   %d  |", p.hand[i].value);
    }
    else {
      printf("  %d  |", p.hand[i].value);
    }
  }
  printf("\nx||");
  for (int j = 0; j < 7; j++) {
    printf(" %s  |", p.hand[j].actionString);
  }
  printf("\n    oo---oo---oo---oo---oo---oo---oo---oo---oo---oo\n");

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
    while(index < MAX_CARDS && fscanf(in, "%d %s", &drawPile[index].value, drawPile[index].action) == 1) { //scans card value and card action
      index++;
      } //drawPile[index].action)==2
  }
}

/***********************************************************************
 * CREATE RANDOM DECK (card deck[]) //empty deck
 ************************************************************************/
void createRandomDeck(card deck[]) { //if user chooses shuffle deck
    char actions[8][15] =  {"swapAdjacent", "swapOver", "moveRight", "moveLeft", "removeLeft", "removeMiddle", "removeRight", "protect"};
    char actionStrings[8][3] = {"SS_", "S_S", "M_R", "M_L", "X__", "_X_", "__X", "XXX"};
    int random;
    for (int i = 0; i < MAX_CARDS; i++) {
      random = rand() % 8;
      card temp;
      temp.used = false;
      temp.value = i;
      strcpy(temp.action, actions[random]);
      strcpy(temp.actionString, actionStrings[random]);
      deck[i] = temp;
    }
}

/***********************************************************************
 * SHUFFLE DECK (card deck[])
 ************************************************************************/
void shuffleDeck(card deck[]) {
  card tempCard;
  for (int i = 0; i < MAX_CARDS; i++) {
    int temp = rand() % 84;
    tempCard = deck[i];
    deck[i] = deck[temp];
    deck[temp] = tempCard;
  }
}

/***********************************************************************
 * PRINT DECK - used to test functionality (not in gameplay)
 ************************************************************************/
void printAvailableDeck(card deck[]) {
  for (int i = 0; i < MAX_CARDS; i++) {
    if (!deck[i].used) {
      printf("Value %d has action %s (%s)\n", deck[i].value, deck[i].action, deck[i].actionString);
    }
  }
}

/***********************************************************************
 * DRAW CARD (card deck[]) Returns card
 ************************************************************************/
card drawCard(card deck[]) {
  int index = rand() % 84;
  card drawn = deck[index];
  while (drawn.used) {
    index = rand() % 84;
    drawn = deck[index];
    deck[index].used = true;
  }
  return drawn;
}

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
  bool used;            // whether or not card can be drawn from drawPile (deck)
  char actionString[4]; // shortened version of action for display
  int actionNum;        // index of action within faceUp line up
} card;

typedef struct {
  card hand[7];
  char name[20];
  int len;              // length of sorted cards starting from index 0, determined if deck has no cards which can be drawn
} player;

int setup(int SIZE, player player_array[], card deck[]);
void quicksort(card cardsarray[], int low, int high);
void swap(card *a, card *b);
int partition(card cardsarray[], int low, int high);
void cardsfile();
void shuffleDeck(card deck[]);
void createRandomDeck(card deck[]);
void printAvailableDeck(card deck[]);
int playRound(player starting_player, card deck[], card faceUp[], int hasFaceUp[], int turn);
card drawCard(card deck[]);
void printHand(player p);
bool checkWin(int SIZE, player player_array[]);
void endGame(player player_array[], int SIZE);

/***********************************************************************
 * MAIN
 * 
 * creates arrays and passes functions for gameplay
 ************************************************************************/
int main()
{
  card deck[MAX_CARDS];
  card faceUp[8];
  int hasFaceUp[8] = {0, 0, 0, 0, 0, 0, 0, 0};  // keeps track of whether action is in faceUp pile
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

  int starting_index = setup(SIZE, player_array, deck);

  while (winner == false){            // gameplay continues until someone has won
    for (int i = 0; i < SIZE; i++){
      if (starting_index < 0) {       // gameplay ends if deck has no cards that can be drawn
        endGame(player_array, SIZE);
      }
      if (starting_index >= SIZE){
        starting_index = 0;
      }
      starting_index = playRound(player_array[starting_index], deck, faceUp, hasFaceUp, i+1);
    }

    if (checkWin(SIZE, player_array)) {
      printf("Game has ended.");
      return 1;
    }
  }
    return 0;
}

/***********************************************************************
 * SETUP (int SIZE, plaer player_array[])
 ************************************************************************/
int setup(int SIZE, player player_array[], card deck[]){
  for (int i = 0; i < SIZE; i++) {
    printf("Enter player %d name: ", i + 1);
    fgets(player_array[i].name, 20, stdin);
  }

  for (int p = 0; p < SIZE; p++){             // generate starting hand of cards for each player
    for (int c = 0; c < 7; c++){
      player_array[p].hand[c] = drawCard(deck);
    }
  }
  for (int i = 0; i <= SIZE; i++){            // sort each players cards in ascending order
    quicksort(player_array[i].hand, 0, 6);
  } 

  for (int p = 0; p < SIZE; p++){             // print each players hand
    printHand(player_array[p]);
  }

  return rand() % SIZE;                       // return random starting player
  //while(){
  //player[i][j] = 0;
  
 }

void quicksort(card cardsarray[], int low, int high) {
    if (low < high) {
        int pivotindex = partition(cardsarray, low, high); // partition the array
        quicksort(cardsarray, low, pivotindex - 1);       // sort cards before partition
        quicksort(cardsarray, pivotindex + 1, high);      // sort cards after partition
    }
}

void swap(card *a, card *b) { // swaps the cards
    card temp = *a;
    *a = *b;
    *b = temp;
}

int partition(card cardsarray[], int low, int high) {
    card pivot = cardsarray[high];
    int i = low - 1; // index of smaller card number

    for (int j = low; j < high; j++) {
        if (cardsarray[j].value >= pivot.value) { // Change comparison to >= for descending order
            i++;
            swap(&cardsarray[i], &cardsarray[j]);
        }
    }
    swap(&cardsarray[i + 1], &cardsarray[high]);
    return i + 1;
}


/***********************************************************************
 * ROUND (player player_array[], card deck[], card faceUp[])
 * Note that the commented parts of this section relate to unfinished 
 * functionality relating to usage and implementation of faceup cards
 ************************************************************************/
int playRound(player starting_player, card deck[], card faceUp[], int hasFaceUp[], int turn) {
  printf("Available face-up cards: ");
  for (int i = 0; i < 8; i++) {
    if (hasFaceUp[i] == 1) {
      printf("%i %s, ", faceUp[i].value, faceUp[i].actionString);
    }
  }
  printf("\n");

  printHand(starting_player);
  printf("Enter 'd' to draw a card or 'f' to select from the face-up cards.\n");
  char nextMove;
  scanf("%c", &nextMove);
  if (nextMove == 'd') {
    printf("\nCard Drawn: ");
    card tempCard = drawCard(deck);
    if (tempCard.value == 100) {        // checks if deck returns value corresponding to an empty drawPile
      return -1;
    }
    printf("%d", tempCard.value);       // show drawn card, play only number value
    printf("%s \n", tempCard.actionString);

    printf("Choose the position of the card you want to change(0 - 6)");
    int position;                       // choose which card from hand will be discarded
    scanf("%i", &position);

    card toFaceUp = starting_player.hand[position];     // discarded card placed into faceUp pile if possible
    if (hasFaceUp[toFaceUp.actionNum] == 0) {
      faceUp[toFaceUp.actionNum] = toFaceUp;
      hasFaceUp[toFaceUp.actionNum] = 1;
    }
    else {
      hasFaceUp[toFaceUp.actionNum] = 0;
    }
  /*
  else if (nextMove == 'f') {
    // face-up option selected and done
  }
  else {
    printf("Invalid move. Next player's turn.");
  }*/

  starting_player.hand[position] = tempCard;

  }

  printHand(starting_player);

  return turn;
}

/***********************************************************************
 * CHECK WIN (player player_array[]) Returns boolean
 ************************************************************************/
bool checkWin(int SIZE, player player_array[]) {
  bool winner = false;
  for (int i = 0; i < SIZE; i++) {
    int length = 0;
    for (int j = 1; j < 7; j++) {
      if (player_array[i].hand[j].value > player_array[i].hand[j-1].value) {
        length++;                       // adds to length only if curr val > previous
      }
      else {
        break;                          // breaks loop if curr val <= prev
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
  printf("%s \n   OOo Oo o\n  O________________________________________________\n ||", p.name);
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
    char actionStrings[8][4] = {"SS_", "S_S", "M_R", "M_L", "X__", "_X_", "__X", "XXX"};
    for (int i = 0; i < MAX_CARDS; i++) {     // creates MAX_CARDS cards and initializes values
      int random = rand() % 8;
      card temp;
      temp.used = false;
      temp.value = i;
      temp.actionNum = random;
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
  for (int i = 0; i < MAX_CARDS; i++) {     // uses Fisher-Yates shuffling alogrithm
    int temp = rand() % MAX_CARDS;          // switches the location of cards randomly around twice per card
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
  int index = rand() % MAX_CARDS;
  for (int i = 0; i < MAX_CARDS; i++) { // checks that at least one card is free to avoid infinite loop
    if (!deck[i].used) {              
      while (deck[index].used) {        // if a card is in play it draws again
        index = rand() % MAX_CARDS;
      }
      deck[index].used = true;          // marks card as used to ensure it isn't drawn twice
      return deck[index];
    }
  }
  card endGame;                         // if drawing a card would result in an infinite loop, returns card with value outside range
  endGame.value = 100;
  return endGame;
}
/***********************************************************************
 * END GAME (player player_array[]) Returns card
 ************************************************************************/

void endGame(player player_array[], int SIZE) {
  player currMax = player_array[0];
  for (int i = 0; i < SIZE; i++) {
    player_array[i].len = 0;
    for (int j = 1; j < 7; j++) {
      if (player_array[i].hand[j].value > player_array[i].hand[j - 1].value) {
        player_array[i].len++;                        // keeps track of length sorted by playerss
      }
    }
    if (player_array[i].len > currMax.len) {
      currMax = player_array[i];
    }
  }
  printf("Draw pile has run out. %s had the longest train. Congratulations!", currMax.name);
}
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

typedef struct {
  int value;
  char action[15];
} card;

typedef struct {
  card hand[7];
} player;

void setup(p);

int main()
{
  int* p; //players 
  printf("Enter the number of players: ");
  scanf("%d", p);
  bool winner = false;

  player player_array[*p]; 

  while (winner = false){
    for(int i = 0; i <= player_array; i++){
      setup(p);
    }
  }
  

    return 0;
}

void setup(int *p){
  
}

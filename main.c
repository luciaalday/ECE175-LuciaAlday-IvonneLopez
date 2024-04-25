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

typedef struct {
  int value;
  char action[15];
} card;

void setup(p);

int main()
{
  int p; //players 
  printf("Enter the number of players: ");
  scanf("%d", &p);
  

    return 0;
}

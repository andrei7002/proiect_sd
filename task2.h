#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task1.h"

struct Q {
    Team *front, *rear;
};
typedef struct Q Queue;

struct s {
    Team *top;
};
typedef struct s Stack;

Queue *createQueue ();
int isEmpty (Queue *q);
void enQueue (Queue *q, Team *t);
Team* deQueue (Queue *q);
void afisareEchipeCoada (FILE *f, Queue *q, int i);

Stack *createStack ();
int isEmptyStack (Stack *s);
void push (Stack *s, Team *t);
Team *pop (Stack *s);

void simulareRunda (Queue *q, Stack *winnerStack, Stack *loserStack);
void freeLoserStack (Stack *loserStack);
void mutareWinnerStack (Stack *winnerStack, Queue *q);
void afisareEchipeStiva (FILE *f, Stack *s, int runda);
Team *copyTeam (Team *original);
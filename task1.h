#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct p {
    char *firstName;
    char *secondName;
    int points;
};
typedef struct p Player;

struct t {
    char *teamName;
    int teamMembers;
    float teamPoints;
    Player *members;
    struct t *next;
};
typedef struct t Team;



void citireEchipe (FILE *f, Team **head);
int powerOf2 (int n);
int numarEchipe (Team *head);
void freeTeam (Team *t);
void eliminareEchipaPunctajMinim (Team **head);
void freeTeams (Team **head);
void afisareEchipe (FILE *f, Team *head);
void freeList (Team **head);

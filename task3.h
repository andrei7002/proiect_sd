#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task1.h"
#include "task2.h"

struct n {
    Team *team;
    struct n *left;
    struct n*right;
};
typedef struct n Node;

Node* newNode (Team *t);
Node* insertNode (Node *node, Team *t);
void parcurgereDRS (FILE *f, Node *root);
void freeTree (Node *root);
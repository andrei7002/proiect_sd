#include "task1.h"
#include "task2.h"
#include "task3.h"

Node* newNode (Team *t) {
    Node *node = (Node*) malloc (sizeof (Node));
    node->team = t;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insertNode (Node *node, Team *t) {
    if (node == NULL) {
        return newNode (t);
    }

    if (t->teamPoints < node->team->teamPoints) {
        node->left = insertNode (node->left, t);
    }

    else if (t->teamPoints > node->team->teamPoints) {
        node->right = insertNode (node->right, t);
    }

    else {
       
        if (strcmp (t->teamName, node->team->teamName) > 0) {
            node->right = insertNode (node->right, t);
        } else {
            node->left = insertNode (node->left, t);
        }
    }

    return node;
}

void parcurgereDRS (FILE *f, Node *root) {
    if (root != NULL) {
        parcurgereDRS (f, root->right);
        fprintf(f, "%-34s-  %.2f\n", root->team->teamName, root->team->teamPoints);
        parcurgereDRS (f, root->left);
    }
}

void freeTree (Node *root) {
    if (root != NULL) {
        freeTree (root->left);
        freeTree (root->right);
        free (root);
    }
}
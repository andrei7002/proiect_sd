#include "task1.h"
#include "task2.h"

Queue *createQueue () {
    Queue *q;
    q = (Queue*) malloc (sizeof (Queue));
    if (q == NULL) 
        return NULL;
    q->front = q->rear = NULL;
    return q;
}

int isEmpty (Queue *q) {
    return (q == NULL || q->front == NULL);
}

void enQueue (Queue *q, Team *t) {
    if (q == NULL || t == NULL) return;
    
    t->next = NULL;

    if (q->rear == NULL) {
        q->rear = t;
    }
    else {
        (q->rear)->next = t;
        (q->rear) = t;
    }

    if (q->front == NULL) 
        q->front = q->rear;

}

Team* deQueue (Queue *q) {
    if (isEmpty (q)) {
        return NULL;
    }

    Team *aux = q->front;
    
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    aux->next = NULL; 
    return aux;
}

void afisareEchipeCoada (FILE *f, Queue *q, int runda) {
    if (q == NULL || q->front == NULL) 
        return;
    
    Team *temp = q->front;
    fprintf (f, "\n--- ROUND NO:%d\n", runda);
    while (temp != NULL && temp->next != NULL) {
        fprintf (f, "%-33s-%33s\n", temp->teamName, temp->next->teamName);
        temp = temp->next->next; 
    }
}



Stack *createStack () {
    Stack *s = (Stack*) malloc (sizeof(Stack));
    if (s != NULL) {
        s->top = NULL;
    }
    return s;
}

int isEmptyStack (Stack *s) {
    return (s == NULL || s->top == NULL);
}

void push (Stack *s, Team *t) {
    if (s == NULL || t == NULL) 
        return;
    t->next = s->top;
    s->top = t;
}

Team *pop (Stack *s) {
    if (isEmptyStack (s)) 
        return NULL;

    Team *extract = s->top;
    s->top = s->top->next;
    extract->next = NULL;

    return extract;
}

void simulareRunda (Queue *q, Stack *winnerStack, Stack *loserStack) {
    while (!isEmpty (q) && q->front->next != NULL) {
        Team *team1 = deQueue (q);
        Team *team2 = deQueue (q);

        if (team1->teamPoints > team2->teamPoints) {
            team1->teamPoints += 1;
            push (winnerStack, team1);
            push (loserStack, team2);
        }
        else {
            team2->teamPoints += 1;
            push (winnerStack, team2);
            push (loserStack, team1);
        }
    }
}

void freeLoserStack (Stack *loserStack) {
    while (!isEmptyStack (loserStack)) {
        Team *loser = pop (loserStack);
        freeTeam (loser);
    }
}

void mutareWinnerStack (Stack *winnerStack, Queue *q) {
    while (!isEmptyStack (winnerStack)) {
        Team *winner = pop (winnerStack);
        enQueue (q, winner);
    }
}

void afisareEchipeStiva (FILE *f, Stack *s, int runda) {
    if (s == NULL || s->top == NULL) 
        return;

    fprintf(f, "\nWINNERS OF ROUND NO:%d\n", runda);
    
    Team *temp = s->top;
    while (temp != NULL) {
        fprintf(f, "%-34s-  %.2f\n", temp->teamName, temp->teamPoints);
        temp = temp->next;
    }
}

Team *copyTeam (Team *original) {
    if (original == NULL) 
        return NULL;

    Team *clona = (Team*) malloc (sizeof (Team));
    
    clona->teamName = (char*) malloc ((strlen (original->teamName) + 1) * sizeof (char));
    strcpy (clona->teamName, original->teamName);
    
    clona->teamPoints = original->teamPoints;
    clona->teamMembers = original->teamMembers;
    
    clona->members = (Player*) malloc (original->teamMembers * sizeof (Player));
    for (int i=0; i < original->teamMembers; i++) {
        clona->members[i].firstName = (char*) malloc ((strlen (original->members[i].firstName) + 1) * sizeof (char));
        strcpy(clona->members[i].firstName, original->members[i].firstName);
        
        clona->members[i].secondName = (char*) malloc ((strlen (original->members[i].secondName) + 1) * sizeof (char));
        strcpy(clona->members[i].secondName, original->members[i].secondName);
        
        clona->members[i].points = original->members[i].points;
    }
    
    clona->next = NULL;
    return clona;
}

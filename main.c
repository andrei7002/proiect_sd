#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task1.h"
#include "task2.h"
#include "task3.h"

int main (int argc, char *argv[]) {
    if (argc < 4) {
        printf ("Eroare: argumente lipsa !!!");
        return 1;
    }

    FILE *f_cerinte = fopen (argv[1], "r");
    FILE *f_date = fopen (argv[2], "r");
    FILE *f_iesire = fopen (argv[3], "wb");
    if (f_cerinte == NULL || f_date == NULL || f_iesire == NULL) {
        printf ("Eroare la deschidere fisiere !!!");
        return 1;
    }

    int task[5];
    for (int i=0; i < 5; i++) {
        fscanf (f_cerinte, "%d", &task[i]);
    }

    Team *Echipe = NULL;
    if (task[0] == 1) { //Task 1 cu deadline 19.04.2026
        citireEchipe (f_date, &Echipe);
        freeTeams (&Echipe);
        afisareEchipe (f_iesire, Echipe);
    }

    Queue *Meciuri = NULL;
    Stack *winnerStack = NULL;
    Stack *loserStack = NULL;
    Team *top8Teams = NULL;
    if (task[1] == 1) { //Task 2 cu deadline 10.05.2026
        
        Meciuri = createQueue ();
        winnerStack = createStack();
        loserStack = createStack();
        
        int echipeRamase = powerOf2 (numarEchipe (Echipe));

        Team *current = Echipe;
        while (current != NULL) {
            Team *next = current->next;
            enQueue (Meciuri, current);  
            current = next;             
        }
        Echipe = NULL;

        int runda = 1;

        while (Meciuri->front != NULL && Meciuri->front->next != NULL) {
            afisareEchipeCoada (f_iesire, Meciuri, runda);
            simulareRunda (Meciuri, winnerStack, loserStack);
            afisareEchipeStiva (f_iesire, winnerStack, runda);

            echipeRamase /= 2;
            if (echipeRamase == 8) {
                Team *temp = winnerStack->top;
                while (temp != NULL) {
                    Team *clona = copyTeam (temp);
                    clona->next = top8Teams;
                    top8Teams = clona;
        
                    temp = temp->next;
                }
            }

            freeLoserStack (loserStack);
            mutareWinnerStack (winnerStack, Meciuri);
            runda++;
        }
        
        free (winnerStack);
        free (loserStack);
        while (!isEmpty (Meciuri)) {
            Team *ultimul = deQueue (Meciuri);
            freeTeam (ultimul);
        }
        free (Meciuri);
        freeList (&Echipe);
    }

    if (task[2] == 1) { //Task 3 cu deadline 34.05.2026
        fprintf(f_iesire, "\nTOP 8 TEAMS:\n");
        
        Node *root = NULL;

        while (top8Teams != NULL) {
            root = insertNode (root, top8Teams);
            top8Teams = top8Teams->next;
        }

        parcurgereDRS (f_iesire, root);
        freeList (&top8Teams);
        freeTree (root);
    }
    
    fclose (f_cerinte);
    fclose (f_date);
    fclose(f_iesire);

   
    return 0;
}
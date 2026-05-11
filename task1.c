#include "task1.h"

void citireEchipe (FILE *f, Team **head) {
    int numarEchipe;
    if (fscanf (f, "%d", &numarEchipe) != 1) 
        return;
        
    for (int i=0; i < numarEchipe; i++) {
        Team *newTeam = (Team*)malloc (sizeof (Team));

        int numarJucatori;
        fscanf (f, "%d", &numarJucatori);
        newTeam->teamMembers = numarJucatori;

        fgetc (f);
        char aux[100];
        if (fgets (aux, sizeof (aux), f) != NULL) {
            int length = strlen (aux);
            while (length > 0 && (aux[length-1] == '\n' || aux[length-1] == '\r' || aux[length-1] == ' ')) {
                aux[length-1] = '\0';
                length--;
            }

            newTeam->teamName = (char*)malloc ((length + 1) * sizeof (char));
            strcpy (newTeam->teamName, aux);
        }

        newTeam->members = (Player*)malloc (numarJucatori * sizeof (Player));
        float sumaPunctaj = 0;
        for (int j=0; j < numarJucatori; j++) {
            int p;
            char n1[50], n2[50];
            fscanf (f, "%s %s %d", n1, n2, &p);

            newTeam->members[j].firstName = (char*)malloc ((strlen (n1) +1) * sizeof (char));
            strcpy (newTeam->members[j].firstName, n1);
            newTeam->members[j].secondName = (char*)malloc ((strlen (n2) +1) * sizeof (char));
            strcpy (newTeam->members[j].secondName, n2);
            newTeam->members[j].points = p;
            
            sumaPunctaj += p;
        }

        newTeam->teamPoints = sumaPunctaj / numarJucatori;

        newTeam->next = *head;
        *head = newTeam;
    }

}

int powerOf2 (int n) {
    int p = 1;
    while (p * 2 <= n) 
        p *= 2;
    return p;
}

int numarEchipe (Team *head) {
    int n=0;
    while (head != NULL) {
        n++;
        head = head->next;
    }

    return n;
}

void freeTeam (Team *t) {
    if (t == NULL) return;

    if (t->teamName != NULL) {
        free (t->teamName);
    }

    if (t->members != NULL) {
        for (int i=0; i < t->teamMembers; i++) {
            if (t->members[i].firstName != NULL) {
                free(t->members[i].firstName);
            }
           
            if (t->members[i].secondName != NULL) {
                free(t->members[i].secondName);
            } 
        }

        free (t->members);
    }

    free (t);
}

void eliminareEchipaPunctajMinim (Team **head) {
    if (*head == NULL) return;

    Team *current = *head;
    Team *prev = NULL;
    Team *minim = *head;
    Team *prevMinim = NULL;
    float minimPunctaj = current->teamPoints;

    while (current != NULL) {
        if (current->teamPoints < minimPunctaj) {
            minimPunctaj = current->teamPoints;
            minim = current;
            prevMinim = prev;
        }

        prev = current;
        current = current->next;
    }

    if (prevMinim == NULL) {
        *head = (*head)->next;
    }
    else {
        prevMinim->next = minim->next;
    }

    freeTeam (minim);
}

void freeTeams (Team **head) {
    int n = numarEchipe (*head);
    int p = powerOf2 (n);
    int deEliminat = n - p;

    for (int i=0; i < deEliminat; i++) {
        eliminareEchipaPunctajMinim (head);
    }
}

void afisareEchipe (FILE *f, Team *head) {
    while (head != NULL) {
        fprintf (f, "%s\n", head->teamName);
        head = head->next;
    }
}

void freeList (Team **head) {
    Team *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        freeTeam (temp);
    }
}
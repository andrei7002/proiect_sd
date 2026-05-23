# SIMULATOR LAN PARTY

Un program în C care simulează un turneu eliminatoriu de e-sports. Ia o listă de echipe, joacă meciurile rundă cu rundă și generează clasamentul final. 

Proiectul este construit de la zero folosind structuri de date clasice pentru a gestiona eficient memoria și logica turneului.

## Cum funcționează?
1. **Calificările (Liste):** Citește echipele din fișier și le elimină pe cele mai slabe până rămâne un număr de echipe ce reprezintă o putere a lui 2 (formatul optim pentru un turneu).
2. **Turneul (Stive & Cozi):** Simulează meciurile 1 la 1. Echipele sunt extrase din coadă, joacă meciul, iar câștigătorii primesc un punct și trec în runda următoare folosind o stivă temporară.
3. **Clasamentul (BST):** Ultimele 8 echipe rămase în turneu sunt salvate într-un arbore binar de căutare pentru a afișa instantaneu clasamentul final, ordonat descrescător.

## Comenzi rapide (via Makefile)

* **Compilare:** `make build`
* **Rulare teste (Checker automat):** `make check`
* **Rulare manuală cu datele din testele Task 1, 2 și 3:** `make run_t1`, `make run_t2`, `make run_t3`
* **Ștergere executabil:** `make clean`

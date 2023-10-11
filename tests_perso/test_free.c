#include "mem_space.h"
#include "mem.h"
#include "mem_os.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define NB_TESTS 4


int main(int argc, char *argv[]) {

    printf("** Début du test de free **\n");

    printf("Tests au nombre de : %d\n", NB_TESTS);

    //init de la mémoire
    mem_init();

    /****** TEST 1 ******/

    printf("\nTest 1 : Free de différentes tailles\n");

    printf("1.1 Test du free de 0 octets\n");

    //devrait échouer dès l'allocation
    void *adr = mem_alloc(0);
    //devrait renvoyer l'erreur de mem_free : "Erreur free : zone = NULL"
    mem_free(adr);

    printf("1.2 Test du free de 1 octet\n");

    //devrait réussir, ne renvoie rien
    adr = mem_alloc(1);
    mem_free(adr);


    /* En soit mem_alloc alloue 10 octets à cause de la conversion en size_t
        En effet, size_t est un entier positif
    printf("Test du free de -10 octets\n");

    adr = mem_alloc(-10);
    mem_free(adr);

    */

    printf("-> Test 1 réussi\n");


    //réinitialisation de la mémoire
    mem_init();

    /****** TEST 2 ******/

    printf("\nTest 2 : Free de la mémoire entière\n");

    //printf("Test du free de la mémoire entière\n");

    //-100 ici car on doit enlever l'espace pour le header (100 est une valeur arbitraire)
    adr = mem_alloc(mem_space_get_size()-100);
    //devrait réussir, ne retourne rien
    mem_free(adr);

    printf("::On retente d'allouer après le free\n");

    adr = mem_alloc(mem_space_get_size()-100);
    assert(adr != NULL);

    printf("-> Test 2 réussi\n");

    //réinisialisation de la mémoire
    mem_init();

    /****** TEST 3 ******/

    printf("\nTest 3 : Free rien du tout\n");

    //printf("Test du free de rien du tout\n");
    //devrait renvoyer l'erreur de mem_free : "Erreur free : zone = NULL"
    mem_free(NULL);

    printf("-> Test 3 réussi\n");

    /****** TEST 5 ******/
/*  possible de savoir si l'adresse nous appartient ???

    printf("\n Test 4 : Free d'une adresse qui ne nous appartient pas\n");

    //printf("Test du free d'une adresse qui ne nous appartient pas\n");

    adr = mem_alloc(1);
    mem_free(adr + 1);

    adr = mem_alloc(1);
    mem_free(adr - 1);

    adr = mem_alloc(1);
    mem_free(adr + 10);

    adr = mem_alloc(1);
    mem_free(adr - 10);

    printf("-> Test 5 réussi\n");
    */
   //réinitialisation de la mémoire
   mem_init();

    /****** TEST 4 ******/

    printf("\nTest 4 : Free d'une adresse qui n'est pas dans la zone de la mémoire\n");

    //printf("Test du free d'une adresse qui n'est pas dans la zone de la mémoire\n");

    printf("4.1 Libération à une adresse allouée (1o.) - taille de la mémoire\n");
    //devrait retourner le erreur : "Erreur free : zone non comprise dans les bornes de la mémoire"
    adr = mem_alloc(1);
    mem_free(adr + mem_space_get_size());

    printf("4.2 Libération à une adresse allouée (1o.) + taille de la mémoire\n");
    //idem
    adr = mem_alloc(1);
    mem_free(adr - mem_space_get_size());

    printf("-> Test 4 réussi\n");

    /****** FIN DES TESTS ******/

    printf("\n** Fin du test de free **\n");

    return 0;

}
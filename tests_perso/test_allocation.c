#include "mem_space.h"
#include "mem.h"
#include "mem_os.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define NB_TESTS 2

int main(int argc, char *argv[]) {

    printf("** Début du test de l'allocation : cas spéciaux **\n");

    //init de la mémoire
    mem_init();

    /****** TEST 1 ******/

    printf("\nTest 1 : Allocation de différentes tailles\n");

    printf("1.1 Test de l'allocation de 0 octets [doit échouer]\n");

    //devrait retourner l'erreur présente dans mem_alloc : "Erreur allocation : Demande d'allouer 0 octets" 
    void *adr = mem_alloc(0);
    assert(adr == NULL);

    printf("1.2 Test de l'allocation de 1 octet [doit réussir]\n");

    //devrait réussir, ne renvoie rien
    adr = mem_alloc(1);
    assert(adr != NULL);


    //le test suivant ne peut pas se faire car la fonction mem_alloc va caster le -10 en size_t 
    //et un size_t ne peut pas être négatif...

/*
    printf("Test de l'allocation de -10 octets\n");

    adr = mem_alloc(-10);
    assert(adr == NULL);

*/
    printf("-> Test 1 réussi\n");



    //réinitialisation de la mémoire
    mem_init();



    /****** TEST 2 ******/

    printf("\nTest 2 : Allocation de la mémoire entière\n");

    printf("2.1 Test de l'allocation de la mémoire entière [doit échouer]\n");

    adr = mem_alloc(mem_space_get_size());
    //doit retourner une erreur
    //pas possible d'allouer toute la taille : il faut laisser de la place pour le header
    assert(adr == NULL);

    printf("2.2 Test de l'allocation de la mémoire entière + 1 octet [doit échouer]\n");

    //idem, erreur
    adr = mem_alloc(mem_space_get_size() + 1);
    assert(adr == NULL);

    printf("2.3 Test de l'allocation de la mémoire entière - 8 octet (taille de l'entête) [doit réussir]\n");

    //devrait réussir, ne renvoie rien
    adr = mem_alloc(mem_space_get_size() - 8);
    assert(adr != NULL);

    printf("-> Test 2 réussi\n");

    /*FIN des tests*/

    printf("\n** Fin du test de l'allocation de cas spéciaux **\n");

    return 0;
}

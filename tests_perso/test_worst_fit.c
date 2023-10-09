#include "mem_space.h"
#include "mem.h"
#include "mem_os.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

    printf("Début du test de l'allocation en worst fit\n");

    //init de la mémoire et init des différents fragments

    mem_init();

    mem_set_fit_handler(&mem_worst_fit);

    //allocation de 10 octets

    void *adr = mem_alloc(10);
    assert(adr != NULL);

    //allocation de 10 octets

    void *adr2 = mem_alloc(10);
    assert(adr2 != NULL);

    //allocation de 10 octets

    void *adr3 = mem_alloc(10);
    assert(adr3 != NULL);

    //allocation de 10 octets

    void *adr4 = mem_alloc(10);
    assert(adr4 != NULL);

    /*** TEST 1 ***/

    printf("Test 1 : Allocation de 10 octets\n");

    mem_free(adr2);
    mem_free(adr3);

    //allocation de 10 octets

    void *adr5 = mem_alloc(10);

    assert(adr5 != NULL);
    assert(adr5 > adr4);

    printf("Test réussi\n");

    /*** TEST 2 ***/

    printf("Test 2 : Allocation de 10 octets après un free de toute la mémoire sauf le dernier bloc\n");

    mem_free(adr);

    //allocation de 10 octets

    void *adr6 = mem_alloc(10);
    assert(adr6 != NULL);
    //le pointeur doit être dans le bloc le plus gros soit le bloc après adr5
    assert(adr6 > adr5);

    printf("Test réussi\n");

    /*** FIN DES TESTS ***/

    printf("Fin du test de l'allocation en worst fit\n");

    return 0;

}
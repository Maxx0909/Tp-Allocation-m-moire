#include "mem_space.h"
#include "mem.h"
#include "mem_os.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

    printf("Début du test de l'allocation en first fit\n");

    //init de la mémoire et init des différents fragments
    mem_init();

    mem_set_fit_handler(&mem_first_fit);

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

    //allocation de 10 octets
    void *adr5 = mem_alloc(10);
    assert(adr5 != NULL);

    //l'adresse de adr5 doit être entre adr et adr3 anciennement adr2
    assert(adr5 < adr3);
    assert(adr5 > adr);

    printf("Test réussi\n");

    /*** TEST 2 ***/

    printf("Test 2 : Allocation de 20 octets après un free de 10\n");

    mem_free(adr3);

    //allocation de 20 octets

    void *adr6 = mem_alloc(20);

    assert(adr6 != NULL);

    //l'adresse de adr6 doit être entre après adr4 car pas la place entre adr5 et adr4
    assert(adr4 < adr6);

    printf("Test réussi\n");
    
    /*** TEST 3 ***/

    printf("Test 3 : Allocation de 10 octets après un free de la première zone mémoire\n");

    mem_free(adr);

    //allocation de 10 octets

    void *adr7 = mem_alloc(10);

    assert(adr7 != NULL);
    assert(adr < adr5);

    printf("Test réussi\n");

    /*** FIN DES TESTS ***/

    printf("Fin du test de l'allocation en first fit\n");

    return 0;

}
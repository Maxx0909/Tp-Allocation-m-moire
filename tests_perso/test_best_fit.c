#include "mem_space.h"
#include "mem.h"
#include "mem_os.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

    printf("** Début du test de l'allocation en best fit **\n");

    //init de la mémoire et init de la stratégie
    mem_init();
    mem_set_fit_handler(&mem_best_fit);

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

    printf("Test 1 : Allocation de 10 octets entre deux zone occupées\n");

    //créer la zone libre entre adr et adr3
    mem_free(adr2);

    //allocation de 10 octets entre adr et adr3
    void *adr5 = mem_alloc(10);
    assert(adr5 != NULL);

    //meilleur solution = plus petite zone ici entre adr et adr3
    assert(adr5 < adr3);

    printf("Test 1 réussi\n");

    /*** TEST 2 ***/

    printf("Test 2 : Allocation entre deux bloc occupé avec plusieurs trous entre les blocs\n");

    mem_init();
    mem_set_fit_handler(&mem_best_fit);

    //allocation de 10 octets
    adr = mem_alloc(15);
    assert(adr != NULL);

    //allocation de 30 octets
    adr2 = mem_alloc(30);
    assert(adr2 != NULL);

    //allocation de 10 octets
    adr3 = mem_alloc(10);
    assert(adr3 != NULL);

    //allocation de 10 octets
    adr4 = mem_alloc(10);
    assert(adr4 != NULL);

    //allocation de 20 octets
    adr5 = mem_alloc(20);
    assert(adr5 != NULL);

    //libération bloc 2 et 4
    mem_free(adr2);
    mem_free(adr4);

    //allocation de 2 octets
    void *adr6 = mem_alloc(2);

    //meilleur solution = plus petite zone ici entre adr3 et adr5
    assert(adr6 < adr5);
    assert(adr6 > adr3);

    printf("Test 2 réussi\n");

    /*** FIN DES TESTS ***/

    printf("\n** Fin du test de l'allocation en best fit **\n");

    return 0;

}
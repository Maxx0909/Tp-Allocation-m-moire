#include "mem_space.h"
#include "mem.h"
#include "mem_os.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define NB_TESTS 3

int main(int argc, char *argv[]) {

    printf("Début du test de l'allocation\n");

    mem_init();

    /****** TEST 1 ******/

    printf("Test 1 : Allocation de différentes tailles\n");

    printf("Test de l'allocation de 0 octets\n");

    void *adr = mem_alloc(0);
    assert(adr == NULL);

    printf("Test de l'allocation de 1 octet\n");

    adr = mem_alloc(1);
    assert(adr != NULL);

    printf("Test de l'allocation de -10 octets\n");

    adr = mem_alloc(-10);
    assert(adr == NULL);

    printf("Test réussi\n");

    /****** TEST 2 ******/

    printf("Test 2 : Allocation de la mémoire entière\n");

    printf("Test de l'allocation de la mémoire entière\n");

    adr = mem_alloc(mem_space_get_size());
    assert(adr != NULL);

    printf("Test de l'allocation de la mémoire entière + 1 octet\n");

    adr = mem_alloc(mem_space_get_size() + 1);
    assert(adr == NULL);

    printf("Test réussi\n");

    printf("Fin du test de l'allocation\n");

}

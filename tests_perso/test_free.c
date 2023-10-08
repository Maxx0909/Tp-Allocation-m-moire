#include "mem_space.h"
#include "mem.h"
#include "mem_os.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define NB_TESTS 4


int main(int argc, char *argv[]) {

    printf("Début du test de free\n");

    printf("Test au nombre de tests : %d\n", NB_TESTS);

    mem_init();

    /****** TEST 1 ******/

    printf("Test 1 : Free de différentes tailles\n");

    printf("Test du free de 0 octets\n");

    void *adr = mem_alloc(0);
    mem_free(adr);

    printf("Test du free de 1 octet\n");

    adr = mem_alloc(1);
    mem_free(adr);

    printf("Test du free de -10 octets\n");

    adr = mem_alloc(-10);
    mem_free(adr);

    printf("Test réussi\n");

    /****** TEST 2 ******/

    printf("Test 2 : Free de la mémoire entière\n");

    printf("Test du free de la mémoire entière\n");

    adr = mem_alloc(mem_space_get_size());
    mem_free(adr);

    printf("on retente d'allouer après le free\n");

    adr = mem_alloc(mem_space_get_size());
    assert(adr != NULL);

    printf("Test réussi\n");

    /****** TEST 3 ******/

    printf("Test 3 : Free rien du tout\n");

    printf("Test du free de rien du tout\n");

    mem_free(NULL);

    printf("Test réussi\n");

    /****** TEST 4 ******/

    printf("Test 4 : Free d'une adresse qui ne nous apprtient pas\n");

    printf("Test du free d'une adresse qui ne nous apprtient pas\n");

    adr = mem_alloc(1);
    mem_free(adr + 1);

    adr = mem_alloc(1);
    mem_free(adr - 1);

    adr = mem_alloc(1);
    mem_free(adr + 10);

    adr = mem_alloc(1);
    mem_free(adr - 10);

    printf("Test réussi\n");

    printf("Fin du test de free\n");

}
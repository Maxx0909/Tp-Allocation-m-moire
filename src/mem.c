//------------------------------------------------------------------------------
// Projet : TP CSE (malloc)
// Cours  : Conception des systèmes d'exploitation et programmation concurrente
// Cursus : Université Grenoble Alpes - UFRIM²AG - Master 1 - Informatique
//------------------------------------------------------------------------------

#include "mem.h"
#include "mem_space.h"
#include "mem_os.h"
#include <assert.h>

//définition de la structure des blocs libre 
typedef struct mem_free_block_s {
	size_t size_free_block;
	mem_free_block_t * ptr_next_free_block;
}mem_free_block_t;

//définition de la structure des blocs occupés
typedef struct mem_busy_block_s {
    size_t size_busy_block;
} mem_busy_block_t;


//définition de la mémoire
typedef struct memory_s {
	char * ptr_memory;
	size_t size_memory;
}memory_t;


//information pour savoir où est le premier bloc libre
memory_t glb_memory;

//-------------------------------------------------------------
// mem_init
//-------------------------------------------------------------
/**
 * Initialize the memory allocator.
 * If already init it will re-init.
**/
void mem_init() {
    //TODO: implement

	glb_memory.size_memory = mem_space_get_size();

	//si la mémoire est déjà alloué on réinitilaise tout
	if(glb_memory.ptr_memory){
		free(glb_memory.ptr_memory);
		
		//TODO: fonction de recherche à réinitialiser

	}

	glb_memory.ptr_memory = malloc(mem_space_get_size());


	//TODO:fct de rechehrche à initialiser


		//init du premier et unique bloc dans la mémoire

	//pointeur sur le début de la mémoire au départ le même que la structure
	mem_free_block_t * first_memory_bloc = (mem_free_block_t *) glb_memory.ptr_memory;

	first_memory_bloc->size_free_block = glb_memory.size_memory - sizeof(mem_free_block_t *);

	first_memory_bloc->ptr_next_free_block = NULL;

	
	//assert(! "NOT IMPLEMENTED !");
}

//-------------------------------------------------------------
// mem_alloc
//-------------------------------------------------------------
/**
 * Allocate a bloc of the given size.
**/
void *mem_alloc(size_t size) {
	//TODO: implement
	assert(! "NOT IMPLEMENTED !");
    return NULL;
}

//-------------------------------------------------------------
// mem_get_size
//-------------------------------------------------------------
size_t mem_get_size(void * zone)
{
    //TODO: implement
	assert(! "NOT IMPLEMENTED !");
    return 0;
}

//-------------------------------------------------------------
// mem_free
//-------------------------------------------------------------
/**
 * Free an allocaetd bloc.
**/
void mem_free(void *zone) {
    //TODO: implement
	assert(! "NOT IMPLEMENTED !");
}

//-------------------------------------------------------------
// Itérateur(parcours) sur le contenu de l'allocateur
// mem_show
//-------------------------------------------------------------
void mem_show(void (*print)(void *, size_t, int free)) {
    //TODO: implement

	//récup taille mémoire
	size_t size_memory = mem_space_get_size();

	//récup pointeur au début mémoire
	char * ptr_memory = mem_space_get_addr();

	char * ptr_current = ptr_memory;

	//tq pas arrivé fin mémoire
	while(ptr_current != (ptr_memory + size_memory)){

		//si le bloc est libre
		if(ptr_current == ){
			print("Adresse : %p", ptr_current, " , taille : %zu", ptr_current->size_free_block, " , Adresse bloc suivant : %p",  ptr_current->ptr_next_free_block, " , occupé : %d",  1);

			//on passe au bloc suivant
			ptr_current = ptr_current + (char *) ptr_current->size_free_block;
		
		//si le bloc est occupé
		} else {
			print("Adresse : %p", ptr_current, " , taille : %zu", ptr_current->size_busy_block, " , occupé : %d", 0);

			//on passe au bloc suivant
			ptr_current = ptr_current + ptr_current->size_busy_block;
		}

	
	}

	//assert(! "NOT IMPLEMENTED !");
}

//-------------------------------------------------------------
// mem_fit
//-------------------------------------------------------------
void mem_set_fit_handler(mem_fit_function_t *mff) {
	//TODO: implement
	assert(! "NOT IMPLEMENTED !");
}

//-------------------------------------------------------------
// Stratégies d'allocation
//-------------------------------------------------------------
mem_free_block_t *mem_first_fit(mem_free_block_t *first_free_block, size_t wanted_size) {
    //TODO: implement
	assert(! "NOT IMPLEMENTED !");
	return NULL;
}
//-------------------------------------------------------------
mem_free_block_t *mem_best_fit(mem_free_block_t *first_free_block, size_t wanted_size) {
    //TODO: implement
	assert(! "NOT IMPLEMENTED !");
	return NULL;
}

//-------------------------------------------------------------
mem_free_block_t *mem_worst_fit(mem_free_block_t *first_free_block, size_t wanted_size) {
    //TODO: implement
	assert(! "NOT IMPLEMENTED !");
	return NULL;
}

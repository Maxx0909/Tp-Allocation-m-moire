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
	size_t size_total_fb;
	mem_free_block_t * ptr_next_fb;
}mem_free_block_t;

//définition de la structure des blocs occupés
typedef struct mem_busy_block_s {
    size_t size_total_bb;
} mem_busy_block_t;

//définition de la mémoire
typedef struct header_memory_s{
	mem_free_block_t * first_fb;
	size_t size_memory;
}header_memory_t;


//information pour savoir où est le premier bloc libre
header_memory_t glb_memory;

//-------------------------------------------------------------
// mem_init
//-------------------------------------------------------------
/**
 * Initialize the memory allocator.
 * If already init it will re-init.
**/
void mem_init() {
    //TODO: implement

	//init de la taille de la mémoire
	glb_memory.size_memory = mem_space_get_size()-1;

	//init du premier et unique bloc dans la mémoire
	mem_free_block_t * first_memory_bloc = (mem_free_block_t *)  mem_space_get_addr();

	first_memory_bloc->ptr_next_fb = NULL;

	first_memory_bloc->size_total_fb = glb_memory.size_memory - sizeof(mem_free_block_t *);

	//init l'adresse de la mémoire
	glb_memory.first_fb = first_memory_bloc;

	//TODO:fct de rechehrche à initialiser
	
	
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

	//on récupére le tout premier bloc libre
	mem_free_block_t * current = glb_memory.first_fb;

	mem_free_block_t * ptr_free_block_before = NULL;
	
	//tq le bloc libre est trop petit et qu'il existe
	while(current && current->size_total_fb < (size + sizeof(mem_busy_block_t))){
		ptr_free_block_before = current;
		current = current->ptr_next_fb;
	}

	//pas de bloc assez grand
	if(!current){
		return NULL;
	}

	// bloc de taille assez grand trouvé à la postition courante

	//création d'un bloc busy
	mem_busy_block_t * new_busy_bloc = (mem_busy_block_t *) current;

	new_busy_bloc->size_total_bb = size;

	//raccorder la liste chainé
	if(ptr_free_block_before){
		ptr_free_block_before->ptr_next_fb = current->ptr_next_fb;
	} else {
		//si current est le premier bloc
		glb_memory.first_fb = current->ptr_next_fb;
	}

	return (void *) new_busy_bloc;

	//assert(! "NOT IMPLEMENTED !");
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


	//récup pointeur au début mémoire
	char * ptr_memory = mem_space_get_addr();
	char * ptr_current = ptr_memory;
	char * end_memory = ptr_memory + mem_space_get_size();
	mem_free_block_t *free_b = glb_memory.first_fb;

	//boucle tant que fin non atteinte
	while(ptr_current != end_memory){
		if (ptr_current == (char *) free_b){
			print(ptr_current,free_b->size_total_fb,1);
			ptr_current = ptr_current + free_b->size_total_fb;
			free_b = free_b->ptr_next_fb;
		} else {
			mem_busy_block_t busyZone = *(mem_busy_block_t*) ptr_current;
			print(ptr_current,busyZone.size_total_bb,0);
			ptr_current = ptr_current + busyZone.size_total_bb;
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

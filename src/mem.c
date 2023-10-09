//------------------------------------------------------------------------------
// Projet : TP CSE (malloc)
// Cours  : Conception des systèmes d'exploitation et programmation concurrente
// Cursus : Université Grenoble Alpes - UFRIM²AG - Master 1 - Informatique
//------------------------------------------------------------------------------

#include "mem.h"
#include "mem_space.h"
#include "mem_os.h"
#include <assert.h>

//macro pour l'alignement mémoire en fonction de l'architecture de la machine
#define ALIGNEMENT 8 

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
	mem_fit_function_t *fit_fct;
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

	//init de la taille de la mémoire
	glb_memory.size_memory = mem_space_get_size();

	//init du premier et unique bloc dans la mémoire
	mem_free_block_t * first_memory_bloc = (mem_free_block_t *)  mem_space_get_addr();

	first_memory_bloc->ptr_next_fb = NULL;

	first_memory_bloc->size_total_fb = glb_memory.size_memory;

	//init l'adresse de la mémoire
	glb_memory.first_fb = first_memory_bloc;

	mem_set_fit_handler(&mem_first_fit);
}

//-------------------------------------------------------------
// mem_alloc
//-------------------------------------------------------------
/**
 * Allocate a bloc of the given size.
**/
void *mem_alloc(size_t size) {
	//TODO: implement

	//gérer cas demande allouer 0 octet
	if(size <= 0){
		fprintf(stderr,"Erreur allocation : Demande d'allouer 0 octets\n");
		return NULL;
	}

	//gérer le fait que la taille soit bien un multiple de ALIGNEMENT pr alignement mémoire
	if(size % ALIGNEMENT != 0){
		size_t size_to_add = ALIGNEMENT - size % ALIGNEMENT;
		size += size_to_add;
	}

	//on récupére le tout premier bloc libre
	mem_free_block_t * free_b = glb_memory.first_fb;

	//gérer cas pas de bloc libre
	if(!free_b){
		fprintf(stderr,"Erreur allocation : Pas de bloc libre\n");
		return NULL;
	}

	//variable pour stocker le bloc libre avant celui courant
	mem_free_block_t * ptr_free_block_before = NULL;
	
	//tq le bloc libre est trop petit et qu'il existe
	while(free_b && free_b->size_total_fb < (size + sizeof(mem_busy_block_t))){
		ptr_free_block_before = free_b;
		free_b = free_b->ptr_next_fb;
	}

	//pas de bloc assez grand
	if(!free_b){
		fprintf(stderr,"Erreur allocation : Pas de bloc assez grand\n");
		return NULL;
	}

		// bloc de taille assez grand trouvé à la postition courante

	//conserver la taille du bloc libre
	size_t size_fb = free_b->size_total_fb;

	//création d'un bloc busy
	mem_busy_block_t * new_busy_bloc = (mem_busy_block_t *) free_b;

	new_busy_bloc->size_total_bb = size + sizeof(mem_busy_block_t);

	//calcul de la taille restante pour s'assurer de pouvoir inserer un bloc libre après le bloc occupé

	size_t remaning_size =  size_fb - new_busy_bloc->size_total_bb;

	//si la taille est suffisante
	if(remaning_size > sizeof(mem_free_block_t)){
		//création d'un nouveau bloc libre
		mem_free_block_t * new_free_bloc;

		//ici cast en void* pour éviter la multiplication par la taille de la struct
		new_free_bloc = (mem_free_block_t *) ( (void *)free_b + new_busy_bloc->size_total_bb);

		//taille nouveau bloc libre
		new_free_bloc->size_total_fb = size_fb - new_busy_bloc->size_total_bb;

			//raccorder la liste chainée
		//si free_b pas le premier bloc
		if(ptr_free_block_before){
			ptr_free_block_before->ptr_next_fb = new_free_bloc;
			new_free_bloc->ptr_next_fb = free_b->ptr_next_fb;
		} else {
			//si free_b est le premier bloc
			glb_memory.first_fb = new_free_bloc;
			new_free_bloc->ptr_next_fb = free_b->ptr_next_fb;
		}

	} else {
		// si la taille n'est pas suffisante on ne crée pas de nouveau bloc libre

		// on raccorde la liste chainée
		if(ptr_free_block_before){
			ptr_free_block_before->ptr_next_fb = free_b->ptr_next_fb;
		} else {
			glb_memory.first_fb = free_b->ptr_next_fb;
		}
		
		//on donne le reste qui ne peut pas être utilisé au bloc occupé
		new_busy_bloc->size_total_bb = new_busy_bloc->size_total_bb + remaning_size;

	}

	//retourne l'adresse du début des données et pas l'adresse de la structure de gestion
	return (void *) (new_busy_bloc + 1); // +1 car multiplication de taille sizeof(mem_busy_bloc)

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

	//gérer cas zone = NULL
	if(zone == NULL){
		fprintf(stderr,"Erreur free : zone = NULL\n");
		return;
	}

		//les ptrs de la liste chainée
	//var pour garder le bloc précédent
	mem_free_block_t * free_precedent_block = NULL;

	//on récupére le tout premier bloc libre
	mem_free_block_t * free_b = glb_memory.first_fb;

	// récupérer le dernier bloc libre
	mem_free_block_t * last_free_b = free_b;
	while (last_free_b && last_free_b->ptr_next_fb != NULL){
		last_free_b = last_free_b->ptr_next_fb;
	}

	

		//le bloc occupé

	//converti le pointeur de la zone en un pointeur de bloc occupé
	// - sizeof(mem_busy_block_t) pr récup adresse du bloc occupé sinon pointe sur adresse de la zone du bloc et on laisse le header du busy bloc
	mem_busy_block_t * ptr_busy_bloc = (mem_busy_block_t *) (zone - sizeof(mem_busy_block_t));

	//taille du bloc occupé
	size_t size_total_busy_bloc = ptr_busy_bloc->size_total_bb;


		//le new free bloc

	//création du nouveau free bloc
	mem_free_block_t * new_free_block;

	//associer le pointeur du free bloc à l'adresse du bloc occupé
	new_free_block = (mem_free_block_t *) ptr_busy_bloc;

	//init des para du new fb

	//pb ici sur la taille du bloc libre ??? taille = taille header fb + taille du bloc occupé ??
	//logiquement nouvelle taille = ancienne taille de tout le bloc occupé en comptant le header du bloc occupé
	new_free_block->size_total_fb = size_total_busy_bloc;
	new_free_block->ptr_next_fb = NULL;


			//4 cas à prendre en compte pour fusion/raccordement liste chainée
		//1 : occupé à gauche et à droite => 1 seul zone à free et raccorder dans la liste
		//2 : occupé à droite => fusion avec le bloc libre à droite et raccorder dans la liste
		//3 : occupé à gauche => fusion avec le bloc libre à gauche et raccorder dans la liste
		//4 : occupé ni à gauche ni à droite => 2 zones à free et raccorder dans la liste

		//raccorder dans la liste chainée

	//cas où notre fb devient le premier fb
	if (new_free_block < free_b || free_b == NULL){
		new_free_block->ptr_next_fb = free_b;
		glb_memory.first_fb = new_free_block;

	} else if (last_free_b && new_free_block > last_free_b){ //cas où notre fb devient le dernier fb
		new_free_block->ptr_next_fb = NULL;
		last_free_b->ptr_next_fb = new_free_block;

	} else { //cas où notre fb il faut inserer entre 2 fb

		//recherche du bloc libre précédant le nouveau bloc libre
		while(free_b && free_b->ptr_next_fb < new_free_block){
			free_b = free_b->ptr_next_fb;
		}

		if(free_b){
			new_free_block->ptr_next_fb = free_b->ptr_next_fb;
			free_b->ptr_next_fb = new_free_block;
		}


	}
	
			//gestion de fusions des blocs libres 

			//fusion à droite si possible (i.e bloc libre collé à droite)

	//possible uniquement si le bloc est pas le dernier
	if(new_free_block->ptr_next_fb != NULL){
		//si le bloc suivant == le bloc courant + la taille du bloc courant
		if(new_free_block->ptr_next_fb == (void*) new_free_block + new_free_block->size_total_fb ){
			new_free_block->size_total_fb = new_free_block->size_total_fb + new_free_block->ptr_next_fb->size_total_fb;
			new_free_block->ptr_next_fb = new_free_block->ptr_next_fb->ptr_next_fb;
		}
	}

		//fusion à gauche si possible

	//possible uniquement si le bloc est pas le premier
	if(new_free_block != glb_memory.first_fb){

		free_precedent_block = glb_memory.first_fb;

		//recherche du bloc précédent le new free bloc
		while(free_precedent_block && free_precedent_block->ptr_next_fb != new_free_block){
			free_precedent_block = free_precedent_block->ptr_next_fb;
		}

		//si le new bloc == bloc précédent + taille du bloc précédent
		if(free_precedent_block && new_free_block == (void*) free_precedent_block + free_precedent_block->size_total_fb){
			free_precedent_block->size_total_fb = free_precedent_block->size_total_fb + new_free_block->size_total_fb;
			free_precedent_block->ptr_next_fb = new_free_block->ptr_next_fb;
		}
	}

		// pas besoin de gerer fusion à droite et à gauche : déjà gérer par les 2 cas précédents

	//assert(! "NOT IMPLEMENTED !");
}

//-------------------------------------------------------------
// Itérateur(parcours) sur le contenu de l'allocateur
// mem_show
//-------------------------------------------------------------
void mem_show(void (*print)(void *, size_t, int free)) {


	//récup pointeur au début mémoire
	char * ptr_memory = mem_space_get_addr();
	char * ptr_current = ptr_memory;

	size_t size_mem = mem_space_get_size();
	char * end_memory = ptr_memory + size_mem;
	//
	mem_free_block_t *free_b = glb_memory.first_fb;

	//boucle tant que fin non atteinte
	while(ptr_current != end_memory){
		if (ptr_current == (char *) free_b){
			print(ptr_current,free_b->size_total_fb,1);
			ptr_current = ptr_current + free_b->size_total_fb;
			free_b = free_b->ptr_next_fb;
		} else {
			mem_busy_block_t *busyZone = (mem_busy_block_t*) ptr_current;
			print(ptr_current,busyZone->size_total_bb,0);
			ptr_current = ptr_current + busyZone->size_total_bb;
		}
	}
}

//-------------------------------------------------------------
// mem_fit
//-------------------------------------------------------------
// sauvegarde du type d'allocation choisie
void mem_set_fit_handler(mem_fit_function_t *mff) {
	glb_memory.fit_fct = mff;
}

//-------------------------------------------------------------
// Stratégies d'allocation
//-------------------------------------------------------------
//renvoi du premier bloc libre de taille supérieur ou égale à wanted_size
mem_free_block_t *mem_first_fit(mem_free_block_t *first_free_block, size_t wanted_size) {

	mem_free_block_t *ptr_current = first_free_block;
	//parcours de la liste des blocs libres, on sort quand NULL ou si la taille totale du ptr_current >= taille voulue
	while (ptr_current && ptr_current->size_total_fb < wanted_size){
		ptr_current = ptr_current->ptr_next_fb;
	}
	//sera à null si pas de bloc trouvé
	return ptr_current;
}
//-------------------------------------------------------------
//renvoi du plus petit bloc libre de taille supérieur ou égale à wanted_size
mem_free_block_t *mem_best_fit(mem_free_block_t *first_free_block, size_t wanted_size) {

	mem_free_block_t *ptr_current = first_free_block;
	mem_free_block_t *min_fb = first_free_block;

	while (ptr_current != NULL){
		//on regarde si la taille courante est sup ou égale à celle voulue ET si elle est inférieure à la taille minimale
		if (ptr_current->size_total_fb >= wanted_size && ptr_current->size_total_fb < min_fb->size_total_fb){
			min_fb = ptr_current;
		}
		ptr_current = ptr_current->ptr_next_fb;
	}
	
	// évaluation pour vérifier que la taille minimale bien sup ou égale à celle voulue
	//(ex: cas où min_db est toujours = first_fb, la condition taille first fb >= taille voulue pas encore évaluée)
	if (min_fb->size_total_fb >= wanted_size){
		return min_fb;
	}
	return NULL;
}

//-------------------------------------------------------------
//renvoi du plus petit bloc libre de taille supérieur ou égale à wanted_size
mem_free_block_t *mem_worst_fit(mem_free_block_t *first_free_block, size_t wanted_size) {

   	mem_free_block_t *ptr_current = first_free_block;
	mem_free_block_t *max_fb = first_free_block;

	while (ptr_current != NULL){
		//on regarde si la taille courante est sup ou égale à celle voulue ET si elle est inférieure à la taille minimale
		if (ptr_current->size_total_fb >= wanted_size && ptr_current->size_total_fb > max_fb->size_total_fb){
			max_fb = ptr_current;
		}
		ptr_current = ptr_current->ptr_next_fb;
	}

	// évaluation pour vérifier que la taille maximale bien sup ou égale à celle voulue
	//(ex: cas où max_db est toujours = first_fb, la condition taille first fb >= taille voulue pas encore évaluée)
	if (max_fb->size_total_fb >= wanted_size){
		return max_fb;
	}
	return NULL;
}


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

typedef struct hashtable *Hashtable;


/*data structure*/
struct data {
    struct data *next;
    char *key;
    int value;
};

/*hashtable structure*/
struct hashtable {
    int size; /*size of table*/
    int n; /*num of elements stored*/
    struct data **table;
};


Hashtable createHash(int size);
Hashtable createInitialHash(void);
static unsigned long hashf(const char *s);
void deleteHash(Hashtable h);
static void expand(Hashtable h);
void insertHash(Hashtable h, const char *key, int value);
int hashSearch(Hashtable h, const char *key);
int alreadyInArr(Hashtable HT, int index, int size, struct data *arr[]);


#define GROWTH 2
#define LOAD_FACTOR 1
#define INITIAL_SIZE 10000000


int alreadyInArr(Hashtable HT, int index, int size, struct data *arr[]){
    struct data *e = HT->table[index];
    
    int j;
    for(j = 0; j < size; j++){
        if(arr[j]->key == e->key){
            return 1;
        }
    }
    return 0;
}

/*initialize hashtable*/
Hashtable createHash(int size){
    Hashtable h;
    int i;
    
    h = malloc(sizeof(*h));
    if (h == NULL){
        perror("Could not allocate");
    }
    
    /*set initial size with no elements*/
    h->size = size;
    h->n = 0;
    h->table = malloc(sizeof(struct data *) * h->size);
    
    /*set elements equal to 0 in table*/
    assert(h->table != 0);
    for (i = 0; i < h->size; i++){
        h->table[i] = 0;
    }
    return h;
}

/*create first hash of set size 1000*/
Hashtable createInitialHash(void){
    return createHash(INITIAL_SIZE);
}

/*hashing function*/
static unsigned long hashf(const char *s){
    unsigned const char *meh;
    unsigned long h = 0;
    
    for (meh = (unsigned const char *) s; *meh; meh++){
        h = *meh + h * 97;
    }
    return h;
}

/*get rid of entry*/
void deleteHash(Hashtable h){
    int i;
    struct data *e;
    struct data *next;
    
    /*free data in each part of table*/
    for(i = 0; i < h->size; i++){
        for(e = h->table[i]; e != 0; e = next){
            next = e->next;
            free(e->key);
            free(e);
        }
    }
    /*free Hashtable*/
    free(h->table);
    free(h);
}

/*expand hashtable*/
static void expand(Hashtable h){
    Hashtable h2; /*new Hashtable*/
    struct hashtable temp; /*temporary structure*/
    int i;
    struct data *e;
    
    h2 = createHash(h->size * GROWTH);
    
    /*insert old hash elements to new hashtable*/
    for(i = 0; i < h->size; i++){
        for(e = h->table[i]; e != 0; e = e->next){
            insertHash(h2, e->key, e->value);
        }
    }
    
    /*make old hashtable new*/
    temp = *h;
    *h = *h2;
    *h2 = temp;
    
    /*get rid of old one*/
    deleteHash(h2);
}

/*insert new word*/
void insertHash(Hashtable h, const char *key, int value){
    struct data *e;
    unsigned long f;
    
    assert(key);
    
    e = malloc(sizeof(*e));
    assert(e);
    
    e->key = strdup(key);
    e->value = value;
    
    f = hashf(key) % h->size;
    
    e->next = h->table[f];
    h->table[f] = e;
    
    h->n++;
    /*printf("%d, %d\n", h->n, h->size);*/
    /*expand table if at limit*/
    if(h->n == (h->size * LOAD_FACTOR - 2)){
        /*printf("expanding\n");*/
        expand(h);
    }
}


/*Look for word*/
int hashSearch(Hashtable h, const char *key){
    struct data *e;
    
    /*look through hashtable*/
    for(e = h->table[hashf(key) % h->size]; e != 0; e = e->next){
        /*see if strings are the same*/
        if(!strcmp(e->key, key)){
            return e->value++;
        }
    }
    /*search failed*/
    return 0;
}

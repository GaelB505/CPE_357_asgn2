#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 1000 /*number of spots in memory*/
#define GROWTH 2
#define LOAD_FACTOR 1
#define INITIAL_SIZE 1000

typedef struct hashtable *Hashtable;

/*data structure*/
struct data {
    struct data *next;
    char *key;
    int *value;
};

/*hashtable structure*/
struct hashtable {
    int size; /*size of table*/
    int n; /*num of elements stored*/
    struct data **table;
};


/*Function calls*/
int validInt(char string[]);
Hashtable createHash(int size);
Hashtable createInitialHash(void);
static unsigned long hashf(const char *s);
void deleteHash(Hashtable h);
static void expand(Hashtable h);
void insertHash(Hashtable h, const char *key, int *value);
int *hashSearch(Hashtable h, const char *key);



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
            free(e->value);
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
void insertHash(Hashtable h, const char *key, int *value){
    struct data *e;
    unsigned long f;
    
    assert(key);
    assert(value);
    
    e = malloc(sizeof(*e));
    assert(e);
    
    e->key = strdup(key);
    e->value = value;
    
    f = hashf(key) % h->size;
    
    e->next = h->table[f];
    h->table[f] = e;
    
    h->n++;
    
    /*expand table if at limit*/
    if(h->n >= (h->size * LOAD_FACTOR - 2)){
        expand(h);
    }
}


/*Look for word*/
int *hashSearch(Hashtable h, const char *key){
    struct data *e;
    
    /*look through hashtable*/
    for(e = h->table[hashf(key) % h->size]; e != 0; e = e->next){
        /*see if strings are the same*/
        if(!strcmp(e->key, key)){
            return e->value;
        }
    }
    /*search failed*/
    return 0;
}

int main(int argc, char *argv[]){
    int wordsToShow = 10;   /* the default value */
    int numFiles = argc;    /* used to track how many files will be read */
    int argSkip;            /* used to track how many rgs to skip */
    int i;
    
    if (argc == 1) {        /* case where no args passed */
        numFiles--;         /* one arg, so no files to be read */
        /* and no optional args */
        
    } else if ((0 == strcmp(argv[1], "-n")) && (argc == 2)) {
        fprintf(stderr, "Usage: ./fw -n <int> file file2 ...\n");
        exit(1);
        
        /* ^^ this test checks if there are any args after -n */
        /* if there aren't any, we know there will be an error */
        
        
        /* at this point, we know we have the correct number of args */
        /* to at least attempt continuing the program */
        
        
    } else if (0 == strcmp(argv[1], "-n")) {    /* else, at least one arg */
        i = validInt(argv[2]);      /* check that -n has proper int after */
        
        if (i == 0) {               /* good, proper int */
            wordsToShow = atoi(argv[2]);
            printf("Show the top %d words.\n", wordsToShow);
            
        } else {
            fprintf(stderr, "Usage: ./fw -n <int> file file2 ...\n");
            exit(1);
        }                           /* bad int, throw error */
        numFiles = numFiles - 3;    /* first 3 args can't be files */
        argSkip = 3;                /* -n was successfully passed, */
        /* skip first 3 args */
        
        
    } else if (0 != strcmp(argv[1], "-n")) {    /* the second arg isn't -n */
        numFiles--;                 /* every arg now will be a file */
        argSkip = 1;                /* no -n, skip only first arg */
    }
    
    /* at this point, we have the number of words to show */
    /* and the number of files we will be reading */
    
    if (numFiles == 0) {
        printf("Read from stdin and display %d words.\n", wordsToShow);
    }
    else {
        int currFile = 0;       /* file being read */
        while (currFile != numFiles) {
            printf("Read file %s and display %d words.\n",
                   argv[currFile + argSkip], wordsToShow);
            currFile++;
        }                   /* Ex, first file is 4th arg */
    }
    
    
    
    return 0;
}


int validInt(char string[]) {
    int count = 0;                          /* iterate through string */
    while (string[count] != '\0') {         /* while not at end of string */
        if (isdigit(string[count]) == 0) {  /* if any char is not a digit, */
            return 1;                       /* return 1 (non int parameter) */
        }
        count++;                            /* otherwise, the value can be */
    }                                       /* converted into a string */
    return 0;
    
}

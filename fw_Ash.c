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
    int value;
};

/*hashtable structure*/
struct hashtable {
    int size; /*size of table*/
    int n; /*num of elements stored*/
    struct data **table;
};


/*Function calls*/
int validInt(char string[]);
char *getWordz(FILE *file, char *word);
int alreadyInArr(Hashtable HT, int index, int size, struct data *arr[]);
Hashtable createHash(int size);
Hashtable createInitialHash(void);
static unsigned long hashf(const char *s);
void deleteHash(Hashtable h);
static void expand(Hashtable h);
void insertHash(Hashtable h, const char *key, int value);
int hashSearch(Hashtable h, const char *key);




int main(int argc, char *argv[]){
    int wordsToShow = 10;   /* the default value */
    int numFiles = argc;    /* used to track how many files will be read */
    int argSkip = 0;            /* used to track how many rgs to skip */
    int i;
    char *word;
    char *key = NULL;
    struct data *arr[1000];
    int arrayIndex = 0;
    
    
    
    if (argc == 1) {        /* case where no args passed */
        numFiles--;         /* one arg, so no files to be read */
        /* and no optional args */
        
    } else if ((0 == strcmp(argv[1], "-n")) && (argc == 2)) {
        fprintf(stderr, "usage: fw [-n num] [file1 [file2 ...] ]");
        exit(1);
        
        /* ^^ this test checks if there are any args after -n */
        /* if there aren't any, we know there will be an error */
        
        
        /* at this point, we know we have the correct number of args */
        /* to at least attempt continuing the program */
        
        
    } else if (0 == strcmp(argv[1], "-n")) {    /* else, at least one arg */
        i = validInt(argv[2]);      /* check that -n has proper int after */
        
        if (i == 0) {               /* good, proper int */
            wordsToShow = atoi(argv[2]);
        } else {
            fprintf(stderr, "usage: fw [-n num] [file1 [file2 ...] ]");
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
        Hashtable HT = createInitialHash();
        word = malloc(sizeof(char) * 50);
        word = getWordz(stdin, word);
        while (word != NULL) {
            printf("%s\n", word);
            free(word);
            word = malloc(sizeof(char) * 50);
            word = getWordz(stdin, word);
        }
        deleteHash(HT);
    }
    else {
        Hashtable HT = createInitialHash();
        int currFile = 0;       /* file being read */
        
        while (currFile != numFiles) {
            FILE *file = fopen(argv[currFile + argSkip], "r");
            word = malloc(sizeof(char) * 50);
            word = getWordz(file, word);
            while (word != NULL) {
                key = word;
                if(hashSearch(HT, key) == 0){
                    insertHash(HT, key, 1);
                }
                free(word);
                word = malloc(sizeof(char) * 50);
                word = getWordz(file, word);
            }
            free(word);
            fclose(file);
            currFile++;
        }
        if(wordsToShow == 0){
            printf("The top %d words (out of %d) are:", wordsToShow, HT->n);
        }
        
        
        if(wordsToShow > HT->n){
            wordsToShow = HT->n;
        }
        
        /*finding top words*/
        struct data *e;
        int prevBigFreq = 0;
        int bigFreq = 0;
        int done = 1;
        
        while(done != 0){
            /*iterate through hashtable*/
            for (i = 0; i < HT->size; i++){
                /*if there is something in hashtable*/
                if((e = HT->table[i]) != 0){
                    /*is it bigger than other frequencies*/
                    if(arr[arrayIndex] == NULL && alreadyInArr(HT, i, arrayIndex, arr) == 0){
                        arr[arrayIndex] = e;
                        bigFreq = e->value;
                    }
                    if(bigFreq <= e->value){
                        if(arrayIndex == 0){
                            arr[arrayIndex] = e;
                            bigFreq = e->value;
                        } else {
                            /*check if we didn't add this yet*/
                            if (!alreadyInArr(HT, i, arrayIndex, arr)){
                                /*add to array and update freq*/
                                arr[arrayIndex] = e;
                                bigFreq = e->value;
                            }
                        }
                    }
                }
            }
            
            if((prevBigFreq != bigFreq) && (arrayIndex > wordsToShow - 1)){
                arr[arrayIndex] = NULL;
                break;
            }
            prevBigFreq = bigFreq;
            bigFreq = 0;
            arrayIndex++;
        }
        
        /*print final result*/
        printf("The top %d words (out of %d) are:\n", wordsToShow, HT->n);
        for(int x = 0; x < wordsToShow; x++){
            printf("\t %d %s\n", arr[x]->value, arr[x]->key);
        }
        deleteHash(HT);
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
    
    /*expand table if at limit*/
    if(h->n >= (h->size * LOAD_FACTOR - 2)){
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


char *getWordz(FILE *file, char* word) {
    int buffer = 50;            /*initial buffer 100 long*/
    int bufferAdd = 50;
    char* temp;                 /*iterate through new*/
    char c;
    int numItems = 0;
    
    temp = word;                        /*function to read line*/
    c = getc(file);                     /*get first char*/
    while (0 == isalpha(c)) {
        if (c == EOF) {                 /*if EOF, return NULL*/
            word = NULL;
            return word;
        }
        c = getc(file);                 /*get next char until alpha found*/
    }
    
    
    while (0 != isalpha(c)) {      /*realloc both if needed*/
        
        c = tolower(c);
        *temp = c;
        temp++;
        numItems++;
        if (numItems == buffer - 10) {
            buffer += bufferAdd;
            word = realloc(word, sizeof(char) * buffer);
            temp = word;
            int i = 0;
            while (i != numItems) {
                temp++;
                i++;
            }
        }
        c = getc(file);
    }
    *temp = '\0';
    
    return word;
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

int alreadyInArr(Hashtable HT, int index, int size, struct data *arr[]){
    struct data *e = HT->table[index];
    
    for(int j = 0; j < size; j++){
        if(arr[j]->key == e->key){
            return 1;
        }
    }
    return 0;
}

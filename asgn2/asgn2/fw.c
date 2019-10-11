#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "hashFuncs.c"
#include "nextWord.c"
#include "sortFuncs.c"
/*Function calls*/

struct data *arr[1000];

int main(int argc, char *argv[]){
    int wordsToShow = 10;   /* the default value */
    int numFiles = argc;    /* used to track how many files will be read */
    int argSkip = 0;            /* used to track how many rgs to skip */
    int i;
    char *word;
    char *key = NULL;
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
    
    /*===================================================================*/
    /*===================================================================*/
    /* at this point, we have the number of words to show */
    /* and the number of files we will be reading */
    
    Hashtable HT = createInitialHash();
    
    if (numFiles == 0) {
        word = malloc(sizeof(char) * 50);
        word = getWords(stdin, word);
        while (word != NULL) {
            key = word;
            if(hashSearch(HT, key) == 0){
                insertHash(HT, key, 1);
            }
            free(word);
            word = malloc(sizeof(char) * 50);
            word = getWords(stdin, word);
        }
        free(word);
    }
    else {
        int currFile = 0;       /* file being read */
        
        while (currFile != numFiles) {
            FILE *file = fopen(argv[currFile + argSkip], "r");
            if (file == NULL) {
                fprintf (stderr,
                         "%s: No such file or directory\n",
                         argv[currFile + argSkip]);
            } else {
                word = malloc(sizeof(char) * 50);
                word = getWords(file, word);
                while (word != NULL) {
                    key = word;
                    if(hashSearch(HT, key) == 0){
                        insertHash(HT, key, 1);
                    }
                    free(word);
                    word = malloc(sizeof(char) * 50);
                    word = getWords(file, word);
                }
                free(word);
                fclose(file);
            }
            currFile++;
        }
    }

    /*===================================================================*/
    /*===================================================================*/
    /*At this point, we have all our words and frequencies*/

    if(wordsToShow == 0){
        printf("The top %d words (out of %d) are:", wordsToShow, HT->n);
    }
    if (HT->n == 0) {
        printf("The top %d words (out of %d) are:\n", wordsToShow, HT->n);
        exit(EXIT_SUCCESS);
    }
    printf("The top %d words (out of %d) are:\n", wordsToShow, HT->n);
    
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
                if(arr[arrayIndex] == NULL &&
                    alreadyInArr(HT, i, arrayIndex, arr) == 0){
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
    sortArray(arr, arrayIndex);
    

    int x;
    for(x = 0; x < wordsToShow; x++){
        printf("%9d %s\n", arr[x]->value, arr[x]->key);
    }
        
    

    deleteHash(HT);
    return 0;
}


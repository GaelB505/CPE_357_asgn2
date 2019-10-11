#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *getWord(FILE *file, char* word);
char *trimWord(char *word);

char *getWord(FILE *file, char* word) {
    int buffer = 50;            /*initial buffer 50 long*/
    int bufferAdd = 50;         /*if realloc necessary*/
    char* temp;                 /*iterate through new*/
    char c;  
    int numItems = 0;           
    
    temp = word;                        
    c = getc(file);                     /*get first char*/
    while (0 == isalpha(c)) {
        if (c == EOF) {                 /*if EOF, return NULL*/
            word = NULL;
            return word;                
        }
        c = getc(file);                 /*get next char until alpha found*/
    }

    while (0 != isalpha(c)) {     /*reading word, continue till nonalpha*/
        c = tolower(c);         
        *temp = c;                /*store char*/          
        temp++;
        numItems++;
        if (numItems == buffer - 10) {     /*realloc if necessary*/
            buffer += bufferAdd;
            word = realloc(word, sizeof(char) * buffer);
            temp = word;
            int i = 0;
            while (i != numItems) {         
                temp++;
                i++;
            }
        }
        c = getc(file);         /*get next char*/
    }
   *temp = '\0';                /*add null termination*/
    
    return word;
}



char *trimWord(char *word) {
    char *trimmed;
    if (word == NULL) {
        return NULL;
    }
    trimmed = malloc(sizeof(char) * (strlen(word) + 1));
    if (word != NULL) {
        trimmed = strcpy(trimmed, word);
    }
    free(word);
    return trimmed;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *getWord(FILE *file, char* word);

char *getWord(FILE *file, char* word) {
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

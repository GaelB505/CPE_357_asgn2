#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *getWord(FILE *file);

char *getWord(FILE *file) {
    int buffer = 50;            /*initial buffer 100 long*/
    int bufferAdd = 50;
    char* newWord;              /*point to new line*/
    char* temp;                 /*iterate through new*/
    char c;  
    int numItems = 0;           

    newWord = malloc(sizeof(char) * buffer);    /*allocate for newWord*/

    temp = newWord;                        /*function to read line*/
    while ((c = getc(file)) != EOF) {      /*realloc both if needed*/
        int isChar;
        isChar = isalpha(c);
        if (isChar == 0) {
            *temp = '\0';
            return newWord;
        } 
        c = tolower(c);
        *temp = c;                          
        temp++;
        numItems++;
        if (numItems == buffer - 10) {      /*realloc if needed*/
            buffer += bufferAdd;
            newWord = realloc(newWord, sizeof(char) * buffer);
            temp = newWord;
            int i = 0;
            while (i != numItems) {         /*return to previous location*/ 
                temp++;
                i++;
            }
        }
    }

    return newWord;
}

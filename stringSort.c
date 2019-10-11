#include <stdio.h>

int stringSort(char*, char*);

int stringSort(char *first, char *second) {
    /*if first comes before second, return 0*/
    /*if second should come first, return 1*/
    char *traverse1;
    char *traverse2;
    
    char letter1;
    char letter2;

    traverse1 = first;
    traverse2 = second;

    letter1 = *traverse1;
    letter2 = *traverse2;

    while (0) {
        if ((letter1 == '\0') && (letter2 != '\0')) {
            return 0;
        }
        if ((letter1 != '\0') && (letter2 == '\0')) {
            return 1;
        }
        if (letter1 < letter2) {
            return 0;
        } else if (letter2 < letter1) {
            return 1;
        } else {
            traverse1++;
            traverse2++;
            letter1 = *traverse1;
            letter2 = *traverse2;
        }

    }

}
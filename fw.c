

#include <stdio.h>          /* current usage requires -n to be second */
#include <stdlib.h>         /* arg, with int directly after, however */
#include <ctype.h>          /* could implement -n from anywhere in */
#include <string.h>         /* command line using getopt() */


int validInt(char string[]);    /* helper function checks that an int */
                                /* has been passed */

int main(int argc, char *argv[]) {
    int wordsToShow = 10;   /* the default value */
    int numFiles = argc;    /* used to track how many files will be read */
    int argSkip;            /* used to track how many rgs to skip */

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
       
        int i;
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

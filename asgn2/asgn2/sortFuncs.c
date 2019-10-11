#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>



int stringSort(char *p1, char *p2);
struct data *sortArray(struct data *arr[], int size);
void printArray(struct data *arr[], int size);


int stringSort(char *first, char *second) {
    /*if first comes before second, return 0*/
    /*if second should come first, return 1*/
    char *traverse1;
    char *traverse2;
    int x = 1;
    char letter1;
    char letter2;
    
    traverse1 = first;
    traverse2 = second;
    
    letter1 = *traverse1;
    letter2 = *traverse2;
    
    while (x == 1) {
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
    return 0;
    
}


struct data *sortArray(struct data *arr[], int size){
    int prevFreq = 0;
    int currBigFreq = 0;
    struct data *e;
    int nextPrintIndx = 0;
    
    /*iterate through array*/
    while(nextPrintIndx < size){
        prevFreq = arr[nextPrintIndx]->value;
        int i;
        for(i = nextPrintIndx+1; i < size; i++){
            
            currBigFreq = arr[i]->value;
            /*if they have the same frequency*/
            if(currBigFreq == prevFreq){
                if(stringSort(arr[nextPrintIndx]->key, arr[i]->key) != 1){
                    e = arr[nextPrintIndx];
                    arr[nextPrintIndx] = arr[i];
                    arr[i] = e;
                }
                prevFreq = currBigFreq;
                currBigFreq = 0;
            } else {
                nextPrintIndx++;
                i = nextPrintIndx;
                prevFreq = arr[nextPrintIndx]->value;
                currBigFreq = 0;
            }
            
        }
        nextPrintIndx++;
    }
    return *arr;
}

void printArray(struct data *arr[], int size){
    printf("[");
    int i;
    for(i = 0; i < size; i++){
        printf("(%s, %d)", arr[i]->key, arr[i]->value);
    }
    printf("]\n");
}

#include <stdio.h>
#define HASHSIZE 1000 /*number of spots in memory*/
static struct nlist *hashtab[HASHSIZE]; /*pointer table*/

unsigned int hash(const char *s){
	unsigned int hashval;
	for (hashval = 0; *s != '\0'; s++){
		hashval = *s + 31 * hashval;
	}
	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s){
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np -> next){
		if (strcmp(s, np->name) == 0){
			return np; /*found*/
		}
	}
	return NULL; /*not found*/
}

int main(int argc, char *argv[]){
	int filenum = argc;
	int wordnum = 10;
	int c;
	FILE *in;

	fseek(in, 0, SEEK_END); /*set pointer to end of file*/
	long fileSize = ftell(in); /*return file position (length)*/
	fseek(in, 0, SEEK_SET); /*set pointer to beginning of file*/

	char *wordloc = malloc(fileSize + 1); /*set memory location based on file size*/
	fread(wordloc, fileSize, 1, in);

	if (filenum == 1){
		printf("No files inputted");
	}
	while (filenum > 1){
		if (argv[2] == )
		in = fopen(argv[1], "r");
		if (file == NULL){
			fprintf(stderr, "Cannot open file")
		} else {

			while (fscanf(in, %s, word) != EOF){ /*while not at end of file*/
				for (int i = 0; word[i]; i++){ 	/*lowercase string*/
					word[i] = tolower(word[i]);
				}


			}
		}
		--filenum;
	}
	return 0;
}
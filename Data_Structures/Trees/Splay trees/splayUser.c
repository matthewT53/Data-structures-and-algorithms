/*
	Name: Matthew Ta
	Date: 20/10/2015
	Description: Uses the splay tree ADT to create some balanced trees
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "splay.h"

#define ASCENDING "A"
#define RANDOM "R"
#define DESCENDING "D"

#define DEBUG

#define MAX_NUM 100

// boolean constants
#define TRUE 1
#define FALSE 0

// usage information
void usage(void);
int *generateValues(const char *order, const int max);
void help(void); 

int main(int argc, char *argv[])
{
	int numValues = 0;	
	char *order = NULL, input;
	int v = 0, found = FALSE, i = 0;
	if (argc != 3){
		usage();
		exit(1);
	}

	order = argv[1];
	numValues = atoi(argv[2]);
	#ifdef DEBUG
	printf("order = %s and numValues = %d\n", order, numValues);
	#endif
	
	int *values = generateValues(order, numValues);

	Tree t = newTree(); // create a new splay tree

	// insert the generated values into the tree
	for (i = 0; i < numValues; i++){
		insertValue(t, values[i]);
	}

	printf(">");
	scanf("%c", &input);
	while (input != 'Q'){
		switch (input){
			case 'I': 
				printf("Enter value to insert: \n"); 
				scanf("%d", &v); insertValue(t, v); 
				break;
			case 'S': 
				printf("Enter value to search: \n"); 
				scanf("%d", &v); 
				found = search(t, v);
				printf("Found: %s\n", (found) ? "TRUE" : "FALSE"); 
				break;
			case 'D': 
				printf("Enter value to delete: \n"); 
				scanf("%d", &v); removeValue(t, v); 
				break;
			case 'P': printTree(t); break;
			case 'Q': break;
			case '?': help(); break;
		}
	
		printf(">");
		scanf("%c", &input);
		// getchar(); // flush out the line feed char
	}
	
	disposeTree(t);
	free(values);
	return EXIT_SUCCESS;
}

void usage(void)
{
	printf("./splay  <order>  <# values to insert>\n");
}

int *generateValues(const char *order, const int max)
{
	int *values = malloc(sizeof(int) * max);
	int i = 0;	
	
	srand(time(NULL));
	if (strcmp(order, ASCENDING) == 0){
		for (i = 0; i < max; i++){
			values[i] = i;
		}
	}

	else if (strcmp(order, DESCENDING) == 0){
		for (i = max; i >= 0; i--){
			values[i] = i;
		}
	}

	else{ // generate in random order
		for (i = 0; i < max; i++){
			values[i] = rand() % MAX_NUM;
		}
	}
	return values;
}

void help(void)
{
	printf("I = insert value into tree.\n");
	printf("S = search for a value in the tree.\n");
	printf("D = delete a value from the tree.\n");
	printf("P = print tree.\n");
	printf("Q = quit.\n");
}

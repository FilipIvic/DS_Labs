/*
7. Napisati program koji pomocu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguciti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Tocnije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.
*/

/*Rjeseno: md i dir*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (100)

struct _dir;
typedef struct _dir* Position;
typedef struct _dir {
	char name[MAX_SIZE];
	Position sibling, child;
} dir;

Position MakeDir(Position root, char* name);
int Dir(Position root);

int main()
{
	return 0;
}

Position MakeDir(Position root, char* name)
{
	Position current = root;
	Position newDirectory = NULL;

	newDirectory = (Position)malloc(sizeof(dir));
	if (newDirectory == NULL) {
		printf("Can't allocate memory!\n");
	}

	strcpy(newDirectory->name, name);
	newDirectory->child = NULL;
	newDirectory->sibling = NULL;

	if (current->child == NULL) {
		current->child = newDirectory;
	}
	else {
		current = current->child;
		while (current->sibling != NULL) {
			current = current->sibling;
		}
		current->sibling = newDirectory;
	}

	return current;
}

int Dir(Position root)
{
	Position current = root;

	if (current->child == NULL) {
		printf("Directory is empty");
	}

	current = current->child;

	while (current != NULL) {
		printf("%s\n", current->name);
		current = current->sibling;
	}

	return 0;
}

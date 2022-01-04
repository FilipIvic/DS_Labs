/*
9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u čvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraća
pokazivač na korijen stabla.
b) Napisati funkciju replace koja će svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat će se u stablo na
slici Slika 2.
c) Prepraviti program na način da umjesto predefiniranog cjelobrojnog polja korištenjem
funkcije rand() generira slučajne brojeve u rasponu <10, 90>. Također, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
dijela zadatka.
*/

/*
Rjeseno pod a), b) i c) 
Ne radi bas najbolje
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct _tree;
typedef struct _tree* Position;
typedef struct _tree {
	int element;
	Position left, right;
} tree;

struct _list;
typedef struct _list* PositionList;
typedef struct _list {
	int element;
	PositionList next;
} list;

Position InsertElement(int element, Position root);
Position CreateNewElement(int element);
int PreorderPrint(Position root);
int InorderPrint(Position root);
int Replace(Position root);
int RandomNumber(int min, int max);
Position InsertRandomElement(Position root);
int PrependList(PositionList head, int element);
PositionList CreateNewElementList(int element);
int PrintInList(Position root, PositionList head);
int PrintList(PositionList head);
int writeListInFile(PositionList head, char* fileName);

int main() 
{
	Position root = NULL;
	Position root2 = NULL;
	list head = { .element = 0, .next = NULL };
	list head2 = { .element = 0, .next = NULL };
	PositionList headP = &head;
	PositionList headP2 = &head2;
	srand(time(NULL));
	
	root = InsertElement(2, root);
	root = InsertElement(5, root);
	root = InsertElement(7, root);
	root = InsertElement(8, root);
	root = InsertElement(11, root);
	root = InsertElement(1, root);
	root = InsertElement(4, root);
	root = InsertElement(2, root);
	root = InsertElement(3, root);
	root = InsertElement(7, root);
	/*PreorderPrint(root);
	Replace(root);
	printf("\n");
	PreorderPrint(root);
	printf("\n");
	InorderPrint(root);
	printf("\n");*/

	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	root2 = InsertRandomElement(root2);
	/*PreorderPrint(root2);
	printf("\n");
	InorderPrint(root2);
	printf("\n");
	printf("\n");
	*/
	PrintInList(root, headP);
	PrintList(headP);
	writeListInFile(headP, "Datoteka1");
	printf("\n");
	PrintInList(root2, headP2);
	PrintList(headP2);
	writeListInFile(headP2, "Datoteka2");
	

	return 0;
}

Position InsertElement(int element, Position root)
{
	Position current = root;
	Position newElement = NULL;

	if (current == NULL) {
		newElement = CreateNewElement(element);
		return newElement;
	}
	else if (element >= current->element) {
		current->left = InsertElement(element, current->left);
	}
	else if (element < current->element) {
		current->right = InsertElement(element, current->right);
	}

	return current;
}

Position CreateNewElement(int element)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(tree));
	if (newElement == NULL) {
		printf("Can't allocate memory!\n");
		return NULL;
	}
	newElement->element = element;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

PositionList CreateNewElementList(int element)
{
	PositionList newElement = NULL;

	newElement = (PositionList)malloc(sizeof(list));
	if (newElement == NULL) {
		printf("Can't allocate memory!\n");
		return NULL;
	}
	newElement->element = element;
	newElement->next = NULL;

	return newElement;
}

int PreorderPrint(Position root)
{
	Position current = root;

	if (current != NULL) {
		printf("%d ", current->element);
		PreorderPrint(current->left);
		PreorderPrint(current->right);
	}

	return 0;
}

int InorderPrint(Position root)
{
	Position current = root;

	if (current != NULL) {
		InorderPrint(current->left);
		printf("%d ", current->element);
		InorderPrint(current->right);
	}

	return 0;
}

int Replace(Position root)
{
	Position current = root;
	int temp = 0;

	if (current == NULL) {
		return 0;
	}

	temp = current->element;
	current->element = Replace(current->left) + Replace(current->right);

	return current->element + temp;
}

int RandomNumber(int min, int max)
{
	 return (rand() % (max - min + 1)) + min;
}

Position InsertRandomElement(Position root)
{
	Position current = root;
	Position newElement = NULL;
	int element = 0;

	element = RandomNumber(11, 89);

	if (current == NULL) {
		newElement = CreateNewElement(element);
		return newElement;
	}
	else if (element >= current->element) {
		current->left = InsertElement(element, current->left);
	}
	else if (element < current->element) {
		current->right = InsertElement(element, current->right);
	}

	return current;
}

int PrependList(PositionList head, int element)
{
	PositionList newElement = NULL;

	newElement = CreateNewElementList(element);

	newElement->next = head->next;
	head->next = newElement;

	return 0;
}

int PrintInList(Position root, PositionList head)
{
	Position current = root;

	if (current != NULL) {
		PrintInList(current->left, head);
		PrependList(head, current->element);
		PrintInList(current->right, head);
	}


	return 0;
}

int PrintList(PositionList head)
{
	PositionList temp = head->next;

	while (temp) {
		printf("%d ", temp->element);
		temp = temp->next;
	}

	return 0;
}

int writeListInFile(PositionList head, char* fileName)
{
	PositionList temp = head->next;
	FILE* fp = NULL;

	fp = fopen(fileName, "w");

	if (!fp)
	{
		perror("File could not be opended!\n");
		return -1;
	}

	while (temp) {
		fprintf(fp, "%d ", temp->element);
		temp = temp->next;
	}

	fclose(fp);

	return 0;
}

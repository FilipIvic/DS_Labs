/*
3. Prethodnom zadatku dodati funkcije :
A.dinamički dodaje novi element iza određenog elementa,
B.dinamički dodaje novi element ispred određenog elementa,
C.sortira listu po prezimenima osoba,
D.upisuje listu u datoteku,
E.čita listu iz datoteke.
*/

/*
Sve rjeseno
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (100)

struct _person;
typedef struct _person* position;

typedef struct _person {

	char name[MAX];
	char surname[MAX];

	int birthYear;

	position next;

} person;


int prependList(position head, char* name, char* surname, int birthYear);
int printList(position first);
int appendList(position head, char* name, char* surname, int birthYear);
position findBySurname(position first, char* surname);
int delete(position head, char* surname);
position findBefore(position head, char* surname);
position createPerson(char* name, char* surname, int birthYear);
int insertAfter(position pos, position newPerson);
//3.zdk
int addAfter(position first, char* afterSurname,  char* name, char* surname, int birthYear); //char* afterSurname je prezime osobe nakon koje ce se dodati nova osoba
int addBefore(position first, char* beforeSurname, char* name, char* surname, int birthYear);  //char* beforeSurname je prezime osobe prije koje ce se dodati nova osoba
int writeListInFile(position first, char* fileName); //funkcija koja upisuje listu u datoteku
int ReadListFromFile(position head, char* fileName); //funkcija koja cita datoteku i to upisuje u listu
int SortList(position head); //funkcija za sortiranje liste
int DeleteList(position head); // funkcija koja brise listu


int main()
{
	person head = { .name = { 0 }, .surname = { 0 }, .birthYear = 0, .next = NULL };

	position p = &head;

	
	prependList(p, "Ivica", "Jovic", 2001);
	prependList(p, "Marija", "Maric", 2001);
	appendList(p, "Ivo", "Ivic", 2001);
	prependList(p, "Jure", "Juric", 1998);
	appendList(p, "Stipe", "Stipic", 1968);
	addAfter(p->next, "Jovic", "Karlo", "Karlic", 1999);
	addBefore(p->next, "Stipic", "Filip", "Filipovic", 1982);
	printList(p->next);
	writeListInFile(p->next, "popisOsoba.txt");
	DeleteList(p);
	printf("\n\nIzbrisali smo listu \n\n");
	printList(p->next);
	ReadListFromFile(p, "popisOsoba.txt");
	printf("\n\nUpisali smo file u listu\n\n");
	printList(p->next);

	return 0;
}

int prependList(position head, char* name, char* surname, int birthYear)
{
	position newPerson = NULL;

	newPerson = createPerson(name, surname, birthYear);

	insertAfter(head, newPerson);

	return 0;
}

int printList(position first)
{
	position temp = first;

	while (temp) {

		printf("Name: %s\nSurname: %s\nbirth year: %d\n\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	return 0;
}

int appendList(position head, char* name, char* surname, int birthYear)
{
	position temp = head;
	position newPerson = NULL;

	while (temp->next != NULL)
		temp = temp->next;

	newPerson = createPerson(name, surname, birthYear);

	insertAfter(temp, newPerson);

	return 0;
}

position findBySurname(position first, char* surname)
{
	position temp = first;

	while (temp && strcmp(temp->surname, surname)) {
		temp = temp->next;
	}

	if (temp == NULL)
	{
		printf("There is no such element!\n");
		return NULL;
	}

	return temp;
}

int delete(position head, char* surname)
{
	position prev = NULL;
	position curr = NULL;

	prev = findBefore(head, surname);

	if (prev == NULL)
	{
		printf("Element isn't found");
		return -1;
	}

	curr = prev->next;
	prev->next = curr->next;

	free(curr);

	return 0;
}

position findBefore(position head, char* surname)
{
	position prev = NULL;
	position curr = NULL;

	prev = head;
	curr = prev->next;

	while (curr && strcmp(curr->surname, surname)) {
		prev = curr;
		curr = prev->next;
	}

	if (curr == NULL)
	{
		return NULL;
	}

	return prev;
}

position createPerson(char* name, char* surname, int birthYear)
{
	position newPerson = NULL;

	newPerson = (position)malloc(sizeof(person));

	if (newPerson == NULL)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int insertAfter(position pos, position newPerson)
{
	newPerson->next = pos->next;
	pos->next = newPerson;

	return 0;
}

int addAfter(position first, char* afterSurname, char* name, char* surname, int birthYear)
{
	position newPerson = NULL;
	position temp = first;

	temp = findBySurname(temp, afterSurname);

	newPerson = createPerson(name, surname, birthYear);

	insertAfter(temp, newPerson);

	return 0;
}

int addBefore(position first, char* beforeSurname, char* name, char* surname, int birthYear)
{
	position newPerson = NULL;
	position temp = first;

	temp = findBefore(temp, beforeSurname);

	newPerson = createPerson(name, surname, birthYear);

	insertAfter(temp, newPerson);

	return 0;
}

int writeListInFile(position first, char* fileName)
{
	FILE* fp = NULL;
	position temp = first;

	fp = fopen(fileName, "w");

	if (!fp)
	{
		perror("File could not be opended!\n");
		return -1;
	}

	while (temp) {
		fprintf(fp, "%s %s %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	fclose(fp);

	return 0;
}

int ReadListFromFile(position head, char* fileName)
{
	FILE* fp = NULL;
	char name[MAX] = { 0 }, surname[MAX] = { 0 };
	int birthYear = 0;

	fp = fopen(fileName, "r");

	if (!fp)
	{
		perror("File could not be opended!\n");
		return -1;
	}

	while (!feof(fp)) {
		if (fscanf(fp, "%s %s %d\n", name, surname, &birthYear) != 3) {
			printf("Pogreska!\n");
		}
		else
			appendList(head, name, surname, birthYear);
	}

	fclose(fp);

	return 0;
}

int SortList(position head)
{
	position temp = head;
	position curr = NULL, prev = NULL, temp1 = NULL;
	position end = NULL;

	while(temp->next != end) {
		prev = temp;
		curr = temp->next;
		while(curr->next != end) {
			if (strcmp(curr->surname, curr->next->surname) > 0)
			{
				temp1 = curr->next;
				prev->next = temp1;
				curr->next = temp1->next;
				temp1->next = curr;

				curr = temp1;
			}
			prev = curr;
			curr = curr->next;
		}
		end = curr;
	}

	return 0;
}

int DeleteList(position head)
{
	position previous = head;
	position current = NULL;

	while (previous->next != NULL) {
		current = previous->next;
		previous->next = current->next;
		free(current);
	}

	return 0;
}

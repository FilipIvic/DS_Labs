/*
2. Definirati strukturu osoba(ime, prezime, godina rođenja) i napisati program koji :
A.dinamički dodaje novi element na početak liste,
B.ispisuje listu,
C.dinamički dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.
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

int main()
{
	person head = { .name = { 0 }, .surname = { 0 }, .birthYear = 0, .next = NULL };

	position p = &head;

	prependList(p, "Ivica", "Juric", 2001);
	prependList(p, "Marija", "Maric", 2001);
	prependList( p, "Ivo", "Ivic", 2001);
	appendList(p, "Jure", "Juric", 1998);
	appendList(p, "Stipe", "Stipic", 1968);
	printList(p->next);
	position find = findBySurname(p->next, "Stipic");
	printf("%s\n\n", find->surname);
	delete(p, "Maric");
	delete(p, "Stipic");
	printList(p->next);
	position find1 = findBySurname(p->next, "Stipic");
	printf("%s\n\n", find1->surname);

	return 0;
}

int prependList(position head, char* name, char* surname, int birthYear)
{
	position newPerson = NULL;

	newPerson = (position)malloc(sizeof(person));

	if (newPerson == NULL)
	{
		perror("Can't allocate memory!\n");
		return -1;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	newPerson->next = head->next;
	head->next = newPerson;

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

	while (temp->next != NULL)
		temp = temp->next;

	prependList(temp, name, surname, birthYear);

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

	if(curr == NULL)
	{ 
		return NULL;
	}
		
	return prev;
}

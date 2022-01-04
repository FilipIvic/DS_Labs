#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE (1024)

struct _Polinom;
typedef struct _Polinom* Position;

typedef struct _Polinom
{
	int koeficijent;
	int potencija;

	Position next;
} Polinom;

int ProcitajIzDatoteke(char* nazivDatoteke, Position head1, Position head2);
int ProcitajRedakIzDatoteke(char* buffer, Position head);
Position KreirajClan(int koeficijent, int potencija);
int SortiraniUnos(Position head, Position noviClan);
int IzbrisiNakon(Position prethodni);
int ZbrojiPolinome(Position first1, Position first2, Position headSuma);
//int Unos(int koeficijent, int potencija, Position position);
int PomnoziPolinome(Position first1, Position first2, Position headUmnozak);
int IspisiPolinom(Position first);

int main()
{
	Polinom head1 = { .koeficijent = 0, .potencija = 0, .next = NULL };
	Polinom head2 = { .koeficijent = 0, .potencija = 0, .next = NULL };
	Polinom headSuma = { .koeficijent = 0, .potencija = 0, .next = NULL };
	Polinom headUmnozak = { .koeficijent = 0, .potencija = 0, .next = NULL };

	ProcitajIzDatoteke("polinomi.txt", &head1, &head2);
	ZbrojiPolinome(head1.next, head2.next, &headSuma);
	PomnoziPolinome(head1.next, head2.next, &headUmnozak);
	printf("\nPolinom prvi: ");
	IspisiPolinom(head1.next);
	printf("\nPolinom drugi: ");
	IspisiPolinom(head2.next);
	printf("\nPolinom zbroja: ");
	IspisiPolinom(headSuma.next);
	printf("\nPolinom umnoska: ");
	IspisiPolinom(headUmnozak.next);
	puts("");

	return 0;
}

int ProcitajIzDatoteke(char* nazivDatoteke, Position head1, Position head2)
{
	FILE* fp = NULL;
	char buffer[MAX_LINE] = { 0 };

	fp = fopen(nazivDatoteke, "r");

	if (NULL == fp) {
		perror("Neuspjesno otvaranje datoteke!\n");
		return -1;
	}

	fgets(buffer, MAX_LINE, fp);
	ProcitajRedakIzDatoteke(buffer, head1);

	fgets(buffer, MAX_LINE, fp);
	ProcitajRedakIzDatoteke(buffer, head2);

	fclose(fp);

	return 0;
}

int ProcitajRedakIzDatoteke(char* buffer, Position head)
{
	char* string = buffer;
	int koeficijent = 0, potencija = 0, n = 0;
	Position noviClan = NULL;
	
	while (strlen(string) > 0) {
		if(sscanf(string, "%d %d %n", &koeficijent, &potencija, &n) != 2) {
			printf("Zapis polinoma u datoteci nije ispravan!\n");
			return -1;
		}
		noviClan = KreirajClan(koeficijent, potencija);

		if (NULL == noviClan) {
			return -1;
		}

		SortiraniUnos(head, noviClan);

		string += n;
	}

	return 0;
}

Position KreirajClan(int koeficijent, int potencija)
{
	Position noviClan = NULL;

	noviClan = (Position)malloc(sizeof(Polinom));

	if (NULL == noviClan) {
		perror("Neuspjesna alokacija memorije");
		return NULL;
	}

	noviClan->koeficijent = koeficijent;
	noviClan->potencija = potencija;
	noviClan->next = NULL;

	return noviClan;
}

int SortiraniUnos(Position head, Position noviClan)
{
	Position temp = head;
	int ukupniKoef = 0;

	while (temp->next != NULL && noviClan->potencija > temp->next->potencija) {
		temp = temp->next;
	}

	if (temp->next == NULL || noviClan->potencija !=temp->next->potencija) {
		noviClan->next = temp->next;
		temp->next = noviClan;
	}
	else{ 
		ukupniKoef = noviClan->koeficijent + temp->next->koeficijent;
		if (ukupniKoef == 0) {
			IzbrisiNakon(temp);
		}
		else {
			temp->next->koeficijent = ukupniKoef;
		}
	}
	
	return 0;
}

int IzbrisiNakon(Position prethodni)
{
	Position position = prethodni->next;
	prethodni->next = position->next;
	free(position);
	
	return 0;
}

int ZbrojiPolinome(Position first1, Position first2, Position headSuma)
{
	Position polinomPrvi = first1;
	Position polinomDrugi = first2;
	Position temp = NULL;
	Position noviClan = NULL;

	while (polinomPrvi != NULL && polinomDrugi != NULL) {
		if (polinomPrvi->potencija == polinomDrugi->potencija) {
			noviClan = KreirajClan(polinomPrvi->koeficijent + polinomDrugi->koeficijent, polinomPrvi->potencija);
			if (NULL == noviClan) {
				return -1;
			}
			SortiraniUnos(headSuma, noviClan);
			polinomPrvi = polinomPrvi->next;
			polinomDrugi = polinomDrugi->next;
		}
		else if (polinomPrvi->potencija > polinomDrugi->potencija) {
			noviClan = KreirajClan(polinomDrugi->koeficijent, polinomDrugi->potencija);
			if (NULL == noviClan) {
				return -1;
			}
			SortiraniUnos(headSuma, noviClan);
			polinomDrugi = polinomDrugi->next;
		}
		else {
			noviClan = KreirajClan(polinomPrvi->koeficijent, polinomPrvi->potencija);
			if (NULL == noviClan) {
				return -1;
			}
			SortiraniUnos(headSuma, noviClan);
			polinomPrvi = polinomPrvi->next;
		}
	}

	if (polinomPrvi != NULL) {
		temp = polinomPrvi;
	}

	if(polinomDrugi != NULL) {
		temp = polinomDrugi;
	}

	while (temp != NULL) {
		noviClan = KreirajClan(temp->koeficijent, temp->potencija);
		if (NULL == noviClan) {
			return -1;
		}
		SortiraniUnos(headSuma, noviClan);
		temp = temp->next;
	}

	return 0;
}

/*
int Unos(int koeficijent, int potencija, Position position)
{
	Position noviClan = KreirajClan(koeficijent, potencija);

	if (NULL == noviClan) {
		return -1;
	}

	noviClan->next = position->next;
	position->next = noviClan;

	position = position->next;

	return 0;
}
*/

int PomnoziPolinome(Position first1, Position first2, Position headUmnozak)
{
	Position polinomPrvi = first1;
	Position polinomDrugi = first2;
	Position pocetak = polinomDrugi;
	Position noviClan = NULL;

	while (polinomPrvi != NULL) {
		polinomDrugi = pocetak;
		while (polinomDrugi != NULL) {
			noviClan = KreirajClan(polinomPrvi->koeficijent * polinomDrugi->koeficijent, polinomPrvi->potencija + polinomDrugi->potencija);
			if (NULL == noviClan) {
				return -1;
			}
			SortiraniUnos(headUmnozak, noviClan);
			polinomDrugi = polinomDrugi->next;
		}
		polinomPrvi = polinomPrvi->next;
	}

	return 0;
}

int IspisiPolinom(Position first)
{
	Position temp = first;

	while (temp != NULL) {
		printf("%dx^%d", temp->koeficijent, temp->potencija);
		temp = temp->next;
		if (temp != NULL)
		{
			if (temp->koeficijent < 0)
				printf("");
			else
				printf("+");
		}
	}

	return 0;
}

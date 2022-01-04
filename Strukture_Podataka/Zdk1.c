#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)

typedef struct _student {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
} student;

int ProcitajBrojRedakaIzDatoteke(char* nazivDatoteke);
student* AlocirajMemorijuIProcitajStudente(int brojStudenata, char* nazivDatoteke);
double IzracunajMaksimalanBrojBodova(student* studenti, int brojStudenata);
int IspisiStudente(student* studenti, int brojStudenata, double maksimalanBrojBodova);

int main()
{
	int brojRedaka = 0;
	student* studenti = NULL;
	double maksimalanBrojBodova = 0;

	brojRedaka = ProcitajBrojRedakaIzDatoteke("studenti.txt");

	studenti = AlocirajMemorijuIProcitajStudente(brojRedaka, "studenti.txt");

	if (studenti == NULL) {
		return 0;
	}

	maksimalanBrojBodova = IzracunajMaksimalanBrojBodova(studenti, brojRedaka);

	IspisiStudente(studenti, brojRedaka, maksimalanBrojBodova);

	return 0;
}

int ProcitajBrojRedakaIzDatoteke(char* nazivDatoteke)
{
	int brojacRedaka = 0;
	FILE* datoteka = NULL;
	char buffer[MAX_LINE] = { 0 };

	datoteka = fopen(nazivDatoteke, "r");

	if (!datoteka) {
		perror("Neuspjesno otvaranje datoteke!\n");
		return -1;
	}

	while (!feof(datoteka)) {
		fgets(buffer, MAX_LINE, datoteka);
		brojacRedaka++;
	}

	fclose(datoteka);

	return brojacRedaka;
}

student* AlocirajMemorijuIProcitajStudente(int brojStudenata, char* nazivDatoteke)
{
	FILE* datoteka = NULL;
	student* studenti = NULL;
	int brojac = 0;

	studenti = (student*)malloc(sizeof(student));

	if (!studenti) {
		perror("Neuspjesna alokacija memorije!\n");
		return NULL;
	}

	datoteka = fopen(nazivDatoteke, "r");

	if (!datoteka) {
		perror("Neuspjesno otvaranje datoteke!\n");
		return NULL;
	}

	while (!feof(datoteka)) {
		fscanf(datoteka, " %s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
		brojac++;
	}

	fclose(datoteka);

	return studenti;
}

double IzracunajMaksimalanBrojBodova(student* studenti, int brojStudenata)
{
	double maksimalanBrojBodova = 0;
	int i = 0;

	for (i = 0; i < brojStudenata; i++) {
		if (studenti[i].bodovi > maksimalanBrojBodova) {
			maksimalanBrojBodova = studenti[i].bodovi;
		}
	}

	return maksimalanBrojBodova;
}

int IspisiStudente(student* studenti, int brojStudenata, double maksimalanBrojBodova)
{
	int i = 0;

	printf("Ispis studenata: \n");
	printf("Ime\t\t prezime\t\t apsolutni broj bodova\t relativan broj bodova\n");

	for (i = 0; i < brojStudenata; i++) {
		printf("%s\t\t %s\t\t\t %.2lf\t\t\t %.2lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi,
			(studenti[i].bodovi / maksimalanBrojBodova) * 100);
	}

	return 0;
}
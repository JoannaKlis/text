#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

char* wczytaj_plik(char* nazwa_pliku)
{
	FILE* wczytany_plik = fopen(nazwa_pliku, "r");
	if (!wczytany_plik)
	{
		printf("Blad otwarcia pliku");
		exit(EXIT_FAILURE);
	}

	fseek(wczytany_plik, 0, SEEK_END);
	long rozmiar_pliku = ftell(wczytany_plik);
	rewind(wczytany_plik);

	char* zawartosc = (char*)malloc(rozmiar_pliku + 1);
	if (!zawartosc)
	{
		printf("Blad alokacji pamieci");
		exit(EXIT_FAILURE);
	}

	fread(zawartosc, 1, rozmiar_pliku, wczytany_plik);
	zawartosc[rozmiar_pliku] = '\0';

	fclose(wczytany_plik);
	return zawartosc;
}

char* zlacz_teksty(char* tekst_1, char* tekst_2, char znak_laczenia)
{
	char* indeks_laczenia = strchr(tekst_1, znak_laczenia);

	if (indeks_laczenia == NULL)
	{
		printf("Nie znaleziono znaku po ktorym mozna polaczyc teksty\n");
		exit(EXIT_FAILURE);
	}

	size_t docelowy_rozmiar = (indeks_laczenia - tekst_1) + strlen(tekst_2) + 2;

	char* zlaczone_teksty = (char*)malloc(docelowy_rozmiar);
	if (!zlaczone_teksty)
	{
		printf("Blad alokacji tablicy\n");
		exit(EXIT_FAILURE);
	}

	strncpy(zlaczone_teksty, tekst_1, indeks_laczenia - tekst_1 + 1);
	zlaczone_teksty[indeks_laczenia - tekst_1 + 1] = '\0';

	strcat(zlaczone_teksty, tekst_2);

	return zlaczone_teksty;
}

int main()
{
	char* zawartosc_tekst_1 = wczytaj_plik("tekst1.txt");
	printf("Tresc pliku tekst1.txt:\n%s\n\n", zawartosc_tekst_1);

	char* zawartosc_tekst_2 = wczytaj_plik("tekst2.txt");
	printf("Tresc pliku tekst2.txt:\n%s\n\n", zawartosc_tekst_2);

	printf("Podaj znak z pierwszego tekstu po ktorym ma nastapic polaczenie tekstow: ");
	char znak_laczenia;
	scanf(" %c", &znak_laczenia);

	char* zlaczony_tekst = zlacz_teksty(zawartosc_tekst_1, zawartosc_tekst_2, znak_laczenia);

	printf("\nTekst po dolaczeniu:\n%s\n", zlaczony_tekst);

	FILE* plik_wynikowy = fopen("wynik.txt", "w");
	if (!plik_wynikowy)
	{
		printf("Blad otwarcia pliku wynik.txt");
		exit(EXIT_FAILURE);
	}
	fprintf(plik_wynikowy, "%s", zlaczony_tekst);
	fclose(plik_wynikowy);

	free(zawartosc_tekst_1);
	free(zawartosc_tekst_2);
	free(zlaczony_tekst);

	return 0;
}

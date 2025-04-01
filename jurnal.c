#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    const char *LUNI[] = {"Ianuarie", "Februarie", "Martie", "Aprilie", "Mai", "Iunie", "Iulie", "August", "Septembrie", "Octombrie", "Noiembrie", "Decembrie"}; // Tablou de string-uri reprezentand numele lunilor anului, folosit din motive estetice//
    printf("Bine ai venit!\n");
    FILE *jurnal[32][12][25];                   // tabloul de fisiere  folosit pentru a simula un jurnal//
    char filename[101], character;              // numele fisierului care va fi deschis; un caracter folosit pentru a citi input-ul de la tastatura in diverse situatii//
    unsigned int zi, luna, an, operatie, creat; // primele 3 variabile (citite de la tastatura) sunt folosite pentru a indica data introdusa de utilizator, operatie este o variabila care indica ce se doreste a se face cu fisierul(citi,modifica), iar creat indica daca fisierul a fost creat anterior(1) sau nu(0)//
    printf("Introduceti data dorita:\n");
    printf("Ziua (1......31)= ");
    scanf("%u", &zi);
    if (zi < 1 || zi > 31)
    {
        printf("Introduceti o valoare intre 1 si 31 pentru zi");
        return 1;
    }
    printf("Luna (1......12)= ");
    scanf("%u", &luna);
    if (luna < 1 || luna > 12)
    {
        printf("Introduceti o valoare intre 1 si 12 pentru luna");
        return 2;
    }
    if ((luna == 4 || luna == 6 || luna == 9 || luna == 11 || luna == 2) && zi == 31)
    {
        printf("Luna %s nu are 31 de zile", LUNI[luna - 1]);
        return 4;
    }
    if (luna == 2 && zi == 30)
    {
        printf("Luna Februarie nu are 30 de zile");
        return 5;
    }
    printf("Anul (2000....2025) = ");
    scanf("%u", &an);
    if (an < 2000 || an > 2025)
    {
        printf("Introduceti o valoare intre 2000 si 2025");
        return 3;
    }
    if (an % 4 != 0 && zi == 29 && luna == 2)
    {
        printf("Luna Februarie nu are 29 de zile in anul %d, intrucat acesta nu este un an bisect", an);
        return 6;
    }
    // in liniile 11-47 : se introduc datele de la utilizator, generandu-se anumite coduri de eroare in anumite situatii//
    sprintf(filename, "file%d_%d_%d.txt", zi, luna, an); // se genereaza filename-ul folosind instructiunea sprintf si input-ul utilizatorului//
    jurnal[zi][luna][an - 2000] = fopen(filename, "r");  // fisierul se deschide initial pentru citire(daca nu exista, se va returna NULL//
    if (jurnal[zi][luna][an - 2000] == NULL)
    {
        jurnal[zi][luna][an - 2000] = fopen(filename, "w"); // daca fisierul nu exista, acesta va fi deschis pentru scriere, instructiune ce va determina crearea lui//
        creat = 0;                                          // fisierul nu fusese creat anterior//
    }
    else
        creat = 1; // fisierul a fost creat anterior//
    if (creat == 0)

        printf("Nu exista informatii in pagina din data de %d %d %d, pentru a crea o pagina de jurnal, apasati tasta 2\n!!!WARNING : Daca introduceti valoarea 1, se va afisa un continut gol \n", zi, luna, an);

    else
    {
        printf("Pentru a citi pagina din jurnal, apasati tasta 1\n");
        printf("Pentru a modifica pagina din jurnal, apasati tasta 2\n");
    }
    scanf("%d", &operatie); // daca se doreste doar citirea paginii de jurnal , operatie va lua valoarea 1; daca se doreste modificarea paginii de jurnal, operatie va lua valoarea 2//
    if (operatie < 1 || operatie > 2)
    {
        printf("Introduceti valoarea 1 sau 2");
        return 7;
    }
    printf("Continutul curent al paginii : \n");
    character = fgetc(jurnal[zi][luna][an - 2000]);
    while (character != EOF)
    {
        printf("%c", character);
        character = fgetc(jurnal[zi][luna][an - 2000]);
    }
    // liniile 73-79 : se afiseaza continutul fisierului pe ecran, caracter cu caracter, pana se intalneste caracterul special EOF//
    printf("\n");
    if (operatie == 2) // daca se doreste modificarea fisierului//
    {
        printf("Daca doriti sa adaugati continut la finalul fisierului, apasati tasta 1\nCand terminati de introdus date apasati combinatia ENTER + CTR+Z + ENTER\n!!!WARNING : Daca fisierul nu contine informatii, selectati optiunea 2\n");
        printf("Daca doriti sa suprascrieti continutul fisierului, apasati tasta 2\nCand terminati de introdus date apasati combinatia ENTER + CTR+Z + ENTER\n");
        scanf("%d", &operatie); // operatie va lua valoarea 1 daca se doreste adaugarea continutului la finalul paginii, fara suprascriere; operatie va lua valoarea 2 daca se doreste suprascrierea paginii//
        if (operatie == 1)
            jurnal[zi][luna][an - 2000] = fopen(filename, "a"); // append adauga continut la finalul fisierului, fara a suprascrie//
        else if (operatie == 2)
        {
            jurnal[zi][luna][an - 2000] = fopen(filename, "w");
            fprintf(jurnal[zi][luna][an - 2000], "%d %s %d \n**************\n", zi, LUNI[luna - 1], an); // se introduce un fel de header al fiecarei pagini de jurnal in cazul in care fisierul este deschis cu modul "w", intrucat acest mod sterge continutul anterior al fisierului //
        }
        else
        {
            printf("Introduceti 1 sau 2");
            return 8;
        }
        character = getchar(); // se ignora 1 sau 2-ul introdus de utilizator pentru a selecta append sau suprascriere//
        character = getchar();
        while (character != EOF)
        {
            fputc(character, jurnal[zi][luna][an - 2000]);
            character = getchar();
        }
        // liniile 99-104 : se introduce caracter cu caracter input-ul utilizatorului, pana se intalneste EOF//
    }
    fclose(jurnal[zi][luna][an - 2000]); // se inchide fisierul//
    return 0;
}

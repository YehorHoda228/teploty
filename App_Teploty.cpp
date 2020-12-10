// App_Teploty.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
//Autor:Yehor Hoda
//05.12.2020

//#include "pch.h"
#include <cwchar>
#include <stdio.h>
#include <conio.h>


#define period 7
#define _CRT_SECURE_NO_WARNINGS


float temps[period];
char days[7][10] = { "pondeli", "utery", "streda" ,"ctvrtek" ,"patek" ,"sobota" ,"nedele" };

void inputTemp()
{
	printf("\nZadani teplot...\n\n");
	for (short i = 0; i < period; i++)
	{
		printf("Zadejte teplotu dle %s: ", days[i % 7]);
		scanf("%f", temps + i);
	}
	printf("\n");
}

void readFromFile()
{
	printf("\nNacitani teploty ze souboru...\n\n");
	printf("Zadejte jmeno souboru: ");
	char fName[255];
	scanf("%s", fName);
	FILE* inF = fopen(fName, "r");
	if (inF != NULL)
	{
		for (short i = 0; i < period; i++)
		{
			fscanf(inF, "%f", temps + i);
		}
		fclose(inF);

	}
	else
		printf("Soubor nenalezen\n");
	printf("\n");
}

void saveToFile()
{
	char fName[255];
	printf("\nUloženi teploty do souboru...\n\n");
	printf("Zadejte jmeno souboru: ");
	scanf("%s", fName);
	FILE* outF = fopen(fName, "w");
	if (outF != NULL)
	{
		for (short i = 0; i < period; i++)
		{
			fprintf(outF, "%.2f\n", temps[i]);
		}
		fclose(outF);
		printf("\n...Data byla ulozena...\n");
	}
	else
		printf("Chyba\n");

	printf("\n");
}

void outputTemp()
{
	printf("\nTydenni prehled teplot...\n\n");
	for (short i = 0; i < period; i++)
	{
		printf("-----------------------\n");
		printf("| %-10s | %7.2f|\n", days[i], temps[i]);
	}
	printf("-----------------------\n");
	printf("\n");
}

void outputDayTemp()
{
	int day;
	printf("\nZadej den [1-po, ..., 7-ne] : ");
	scanf("%d", &day);
	printf("V den %d - %s je teplota %.2fst.C.\n\n\n", day, days[day - 1], temps[day - 1]);
}

void inputDayTemp()
{
	int day;
	printf("\nZadej den [1-po, ..., 7-ne] : ");
	scanf("%d", &day);
	printf("\nZadej teplotu: ");
	scanf("%f", temps + (day - 1));
	printf("\n\n");
}
void stat()
{
	double sum = 0, max = temps[0];
	char flag = '0';
	int maxIndex = 0;
	for (int i = 0; i < period; i++)
	{
		sum = sum + temps[i];
		if (temps[i] > max)
		{
			max = temps[i];
			maxIndex = i;
		}
	}
	printf("\n**********************************");
	printf("\nPrumerna denni teplota je %.2fst.C.\n", sum / period);
	printf("Maximalni teplota %.2fst.C. nastala v %s (%d den)\n", max, days[maxIndex], maxIndex + 1);
	for (int i = 0; i < period; i++)
	{
		for (int j = 0; j < period; j++)
		{
			if (i == j) continue;
			if (temps[i] == temps[j] && i < j)
			{
				if (flag == '0')
				{
					printf("Dny se stejnou teplotou %.2fst.C. : %s", temps[i], days[i]);
					flag = '1';
				}
				printf(", %s", days[j]);
			}
			else if (temps[i] == temps[j] && i > j)
				break;
		}
		if (flag == '1')
		{
			printf("\n");
			flag = '0';
		}

	}


	printf("\n**********************************\n");
}
int main()
{
	FILE* inpF = fopen("input.txt", "r");
	if (inpF != NULL)
	{
		for (short i = 0; i < period; i++)
		{
			fscanf(inpF, "%f", temps + i);
		}
		fclose(inpF);
	}
	else
	{
		for (short i = 0; i < period; i++)
		{
			temps[i] = 0;
		}
	}
	char key;
	do
	{
		printf("0. Konec;\n");
		printf("1. Zadat teploty na klavesnici;\n");
		printf("2. Nacist teploty ze souboru;\n");
		printf("3. Ulozit teploty do souboru;\n");
		printf("4. Zobrazit teploty;\n");
		printf("5. Zobrazit teplotu v zadany den (cislo od 1 do 7);\n");
		printf("6. Zmena teploty v zadany den (cislo od 1 do 7);\n");
		printf("7. Statistika teplot\n");
		do
		{
			key = getch();
		} while (key != '1' && key != '2' && key != '3' && key != '4'
			&& key != '0' && key != '5' && key != '6' && key != '7');
		switch (key)
		{
		case '0':
			break;
		case '1':
			inputTemp();
			break;
		case '2':
			readFromFile();
			break;
		case '3':
			saveToFile();
			break;
		case '4':
			outputTemp();
			break;
		case '5':
			outputDayTemp();
			break;
		case '6':
			inputDayTemp();
			break;
		case '7':
			stat();
			break;
		default:
			continue;
			break;
		}


	} while (key != '0');


	return 0;
}




#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdio.h>
#include <io.h>
#include <time.h>
using namespace std;

FILE *archivio;

struct struttura_interrogazione
{
	int codice;
	int alunno;
	int materia;
	int ambito;
	char data[11];
	float voto;
}inter;

int n_interrogazioni = 25;
int n_alunni = 19;
int n_materie = 9;
int n_ambiti = 3;
int voto_max = 10;
int voto_min = 4;
char file[] = "4BINF.itr";

int main()
{
	inter.codice = 0;
	archivio = fopen(file,"w");
	for(int i=0;i<n_interrogazioni;i++)
	{
		if(i%24 == 0)
			srand(time(NULL));
		inter.materia = (rand()%n_materie)+1;
		inter.alunno = (rand()%n_alunni)+1;
		inter.ambito = (rand()%n_ambiti)+1;
		float voto = (rand()%(voto_max-voto_min))+voto_min;
		float v = rand()%10;
		v/=10;
		voto+=v;
		inter.voto = voto;
		inter.codice++;
		strcpy(inter.data,"01/01/2016");
		fwrite(&inter,sizeof(inter),1,archivio);
	}
	fclose(archivio);
}

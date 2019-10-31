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

int main()
{
	archivio = fopen("4BINF.itr","r+");
	fseek(archivio,0,0);
	for(int i=0;i<101;i++)
	{
		fread(&inter,sizeof(inter),1,archivio);
		cout<<inter.codice<<" "<<inter.voto<<endl;
	}
	fclose(archivio);
	system("PAUSE");
}

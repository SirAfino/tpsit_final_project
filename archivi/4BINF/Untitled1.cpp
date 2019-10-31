#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdio.h>
#include <io.h>
using namespace std;

FILE *archivio;
FILE *appoggio;

struct struttura_alunno
{
	int codice;
	char nominativo[20];
	char data_nascita[11];
	char sesso;
}alunno;

int main()
{
	archivio = fopen("4BINF.aln","w");
	alunno.codice=0;
	strcpy(alunno.data_nascita,"11/11/1111");
	alunno.sesso = 'M';
	
	alunno.codice++;
	strcpy(alunno.nominativo,"ALESSIO/LAMBERTO");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"ANTONAZZO/FRANCESCO");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"BENLAHOUAR/ANTONIO");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"CAZZATO/EMANUELE");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"CHIARELLO/MATTEO");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"COSI/MATTEO");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"DAMIANO/ERNESTO");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"DE NUCCIO/GIUSEPPE");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"MARTELLA/GABRIELE");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"MONSELLATO/DANILO");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"NESCA/VITO");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"NICOLARDI/RENATO");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"ORLANDO/ALESSIO");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"ORLANDO/MAURO");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"PIZZOLANTE/MARCO");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"SERAFINO/GABRIELE");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"SERGI/LUCA");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"SERGI/SALVATORE D");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	alunno.codice++;
	strcpy(alunno.nominativo,"SERGI/SALVATORE M");
	fwrite(&alunno,sizeof(alunno),1,archivio);
	
	fclose(archivio);
}

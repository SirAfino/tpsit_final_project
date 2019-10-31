#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdio.h>
#include <io.h>
#include "funzioni_base.cpp"
#include "strutture.cpp"
using namespace std;

void stampa_aiuto(char riga1[], char riga2[]);
void stampa_errore(char riga1[], char riga2[]);
void clear_errore();
void stampa_struttura();
int menu_interattivo_principale(bool f1,bool f2,bool f3);
void stampa_cornice(int colAS,int rigAS,int colAD,int rigAD,char titolo[]);
int menu_interattivo_materie();

void stampa_aiuto(char riga1[], char riga2[])
{
	clear(0,23,24,24);
	stampa_distanza(riga1,23,1,'s');
	stampa_distanza(riga2,24,1,'s');
	gotoxy(0,0);
}

void stampa_errore(char riga1[], char riga2[])
{
	clear(56,23,79,24);
	stampa_distanza(riga1,23,1,'d');
	stampa_distanza(riga2,24,1,'d');
	gotoxy(0,0);
}

void clear_errore()
{
	clear(56,23,79,24);
}

void stampa_struttura()
{
	setcolor(0|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY);
	system("CLS");
	for(int i=0;i<80;i++)
	{
		gotoxy(i,2);cout<<(char)196;
		gotoxy(i,22);cout<<(char)196;
	}
	for(int i=0;i<2;i++)
	{
		gotoxy(25,i);cout<<(char)179;
		gotoxy(55,i);cout<<(char)179;
		gotoxy(25,i+23);cout<<(char)179;
		gotoxy(55,i+23);cout<<(char)179;
	}
	gotoxy(25,2);cout<<(char)193;
	gotoxy(55,2);cout<<(char)193;
	gotoxy(23,22);cout<<(char)193;
	gotoxy(57,22);cout<<(char)193;
	gotoxy(25,22);cout<<(char)194;
	gotoxy(55,22);cout<<(char)194;
	gotoxy(23,2);cout<<(char)194;
	gotoxy(57,2);cout<<(char)194;
	for(int i=3;i<22;i++)
	{
		gotoxy(23,i);cout<<(char)179;
		gotoxy(57,i);cout<<(char)179;
	}
	stampa_distanza("I.I.S.S. G.SALVEMINI",0,1,'s');
	stampa_distanza("ALESSANO",1,1,'s');
	setcolor(12|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY);
	centra("  GESTIONE INTERROGAZIONI",0);
	stampa_distanza("HELP IN LINEA",3,4,'s');
	setcolor(0|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY);
	stampa_distanza("SERAFINO GABRIELE",0,1,'d');
	stampa_distanza("4B INFORMATICA 15/16",1,1,'d');
}

int menu_interattivo_principale(bool f1,bool f2,bool f3)
{
	int tasto,riga_partenza = 6;
	char opzioni[7][20] = {"ARCHIVIO","CLASSE","MATERIE","ALUNNI","INTERROGAZIONI","RISULTATI","ESCI"};
	bool opzioni_abilitate[7] = {true,true,true,true,true,true,true};
	for(int i=0;i<7;i++)
		centra(opzioni[i],6+i);
	colore("GIALLO");
	centra(opzioni[0],6);
	if(!f2)
	{
		colore("GRIGIO");
		for(int i=2;i<6;i++)
		{
			centra(opzioni[i],6+i);
			opzioni_abilitate[i] = false;
		}
	}
	if(!f1)
	{
		centra(opzioni[1],7);
		opzioni_abilitate[1] = false;
	}
	if(!f3)
	{
		colore("GRIGIO");
		centra(opzioni[4],10);
		opzioni_abilitate[4] = false;
	}
	colore("NERO");
	int scelta=0;
	do{
		int next = -1,back = -1;
		if(scelta > 0)
		for(int i=scelta-1;i>=0 && back == -1;i--)
		{
			if(opzioni_abilitate[i])
				back = i;
		}
		if(scelta < 7)
		for(int i=scelta+1;i<7 && next == -1;i++)
		{
			if(opzioni_abilitate[i])
				next = i;
		}
		gotoxy(0,0);tasto = getch();
		switch(tasto)
		{
			case 72:if(back != -1)
					{
						colore("NERO");
						centra(opzioni[scelta],riga_partenza+scelta);
						scelta = back;
						colore("GIALLO");
						centra(opzioni[scelta],riga_partenza+scelta);
					}
					break;
			case 80:if(next != -1)
					{
						colore("NERO");
						centra(opzioni[scelta],riga_partenza+scelta);
						scelta = next;
						colore("GIALLO");
						centra(opzioni[scelta],riga_partenza+scelta);
					}
					break;	
		}
	}while(tasto != 13);
	colore("NERO");
	return scelta+1;
}

int menu_interattivo_archivi()
{
	clear(24,3,56,21);
	colore("ROSSO");
	centra("ARCHIVIO",3);
	colore("NERO");
	int tasto,riga_partenza = 6;
	char opzioni[3][20] = {"CREA/SELEZIONA","ELIMINA","INDIETRO"};
	bool opzioni_abilitate[3] = {true,true,true};
	for(int i=0;i<3;i++)
		centra(opzioni[i],6+i);
	colore("GIALLO");
	centra(opzioni[0],6);
	colore("NERO");
	int scelta=0;
	do{
		int next = -1,back = -1;
		if(scelta > 0)
		for(int i=scelta-1;i>=0 && back == -1;i--)
		{
			if(opzioni_abilitate[i])
				back = i;
		}
		if(scelta < 3)
		for(int i=scelta+1;i<3 && next == -1;i++)
		{
			if(opzioni_abilitate[i])
				next = i;
		}
		gotoxy(0,0);tasto = getch();
		switch(tasto)
		{
			case 72:if(back != -1)
					{
						colore("NERO");
						centra(opzioni[scelta],riga_partenza+scelta);
						scelta = back;
						colore("GIALLO");
						centra(opzioni[scelta],riga_partenza+scelta);
					}
					break;
			case 80:if(next != -1)
					{
						colore("NERO");
						centra(opzioni[scelta],riga_partenza+scelta);
						scelta = next;
						colore("GIALLO");
						centra(opzioni[scelta],riga_partenza+scelta);
					}
					break;
			case 73:colore("NERO");return -1;
			case 81:colore("NERO");return -2;	
		}
	}while(tasto != 13);
	return scelta+1;
}

void stampa_lista_archivi(char lista[][20],int pag,int n_arc)
{
	clear(0,3,22,21);
	colore("ROSSO");
	stampa_distanza("HELP IN LINEA",3,4,'s');
	colore("NERO");
	gotoxy(1,5);cout<<"ARCHIVI PRESENTI";
	int n_pag = n_arc/13;
	if(n_arc%13 != 0)
		n_pag++;
	int arc_da_stampare = n_arc - (pag-1)*13;
	if(arc_da_stampare>13)
		arc_da_stampare = 13;
	gotoxy(14,21);
	printf("PAG %02d/%02d",pag,n_pag);
	if(pag>0)
		for(int i=0;i<arc_da_stampare;i++)
		{
			scrivi(lista[i+(pag-1)*13],2,7+i,21);
		}
}

void stampa_cornice(int colAS,int rigAS,int colAD,int rigAD,char titolo[])
{
	int i;
    char vsx,orizz=(char)196,vdx;
    vsx=(char)218;vdx=(char)191;
    gotoxy(colAS,rigAS);
    cout<<vsx;
    for(i=colAS+1;i<colAD;i++)
    {cout<<orizz;
    }
    cout<<vdx;
    vsx=(char)192;vdx=(char)217;
    gotoxy(colAS,rigAD);
    cout<<vsx;
    for(i=colAS+1;i<colAD;i++)
    {cout<<orizz;
    }
    cout<<vdx;
    char vert=(char)179;
    for(i=rigAS+1;i<rigAD;i++)
    {
	  gotoxy(colAS,i);cout<<vert;
      gotoxy(colAD,i);cout<<vert;
    }
    appunta(titolo,colAS-colAD-4);
    gotoxy(colAS+2,rigAS);
    cout<<titolo;
}

void stampa_text_box(int riga,int l)
{
	colore("NERO");
	l+=2;
	int x1,x2;
	x1 = 40-l/2;
	x2 = x1+l-1;
	stampa_cornice(x1,riga-1,x2,riga+1,"");
}

int menu_interattivo_materie()
{
	clear(24,3,56,21);
	colore("ROSSO");
	centra("MATERIE",3);
	colore("NERO");
	int tasto,riga_partenza = 6;
	char opzioni[4][20] = {"AGGIUNGI","MODIFICA","ELIMINA","INDIETRO"};
	bool opzioni_abilitate[4] = {true,true,true,true};
	for(int i=0;i<4;i++)
		centra(opzioni[i],6+i);
	colore("GIALLO");
	centra(opzioni[0],6);
	colore("NERO");
	int scelta=0;
	do{
		int next = -1,back = -1;
		if(scelta > 0)
		for(int i=scelta-1;i>=0 && back == -1;i--)
		{
			if(opzioni_abilitate[i])
				back = i;
		}
		if(scelta < 4)
		for(int i=scelta+1;i<4 && next == -1;i++)
		{
			if(opzioni_abilitate[i])
				next = i;
		}
		gotoxy(0,0);tasto = getch();
		switch(tasto)
		{
			case 72:if(back != -1)
					{
						colore("NERO");
						centra(opzioni[scelta],riga_partenza+scelta);
						scelta = back;
						colore("GIALLO");
						centra(opzioni[scelta],riga_partenza+scelta);
					}
					break;
			case 80:if(next != -1)
					{
						colore("NERO");
						centra(opzioni[scelta],riga_partenza+scelta);
						scelta = next;
						colore("GIALLO");
						centra(opzioni[scelta],riga_partenza+scelta);
					}
					break;
			case 73:colore("NERO");return -1;
			case 81:colore("NERO");return -2;	
		}
	}while(tasto != 13);
	colore("NERO");
	return scelta+1;
}

void stampa_lista_materie(struct struttura_materia lista[],int pag,int n)
{
	clear(0,3,22,21);
	colore("ROSSO");
	stampa_distanza("HELP IN LINEA",3,4,'s');
	colore("NERO");
	gotoxy(1,5);cout<<"MATERIE PRESENTI";
	int n_pag = n/13;
	if(n%13 != 0)
		n_pag++;
	int arc_da_stampare = n - (pag-1)*13;
	if(arc_da_stampare>13)
		arc_da_stampare = 13;
	gotoxy(14,21);
	printf("PAG %02d/%02d",pag,n_pag);
	if(pag>0)
	for(int i=0;i<arc_da_stampare;i++)
	{
		gotoxy(2,7+i);printf("%02d - ",lista[i+(pag-1)*13].codice);
		scrivi(lista[i+(pag-1)*13].nome,7,7+i,21);
	}
}

void stampa_lista_alunni(struct struttura_alunno lista[],int pag,int n)
{
	clear(0,3,22,21);
	colore("ROSSO");
	stampa_distanza("HELP IN LINEA",3,4,'s');
	colore("NERO");
	gotoxy(1,5);cout<<"ALUNNI PRESENTI";
	int n_pag = n/13;
	if(n%13 != 0)
		n_pag++;
	int arc_da_stampare = n - (pag-1)*13;
	if(arc_da_stampare>13)
		arc_da_stampare = 13;
	gotoxy(14,21);
	printf("PAG %02d/%02d",pag,n_pag);
	if(pag>0)
	for(int i=0;i<arc_da_stampare;i++)
	{
		gotoxy(2,7+i);printf("%02d - ",lista[i+(pag-1)*13].codice);
		scrivi(lista[i+(pag-1)*13].nominativo,7,7+i,23);
	}
}

void stampa_lista_interrogazioni(struct struttura_interrogazione lista[],int pag,int n,struct struttura_materia mat[],struct struttura_alunno aln[])
{
	clear(0,3,22,21);
	colore("ROSSO");
	stampa_distanza("HELP IN LINEA",3,4,'s');
	colore("NERO");
	gotoxy(1,5);cout<<"INTERROG. PRESENTI";
	int n_pag = n/13;
	if(n%13 != 0)
		n_pag++;
	int arc_da_stampare = n - (pag-1)*13;
	if(arc_da_stampare>13)
		arc_da_stampare = 13;
	gotoxy(14,21);
	printf("PAG %02d/%02d",pag,n_pag);
	if(pag>0)
	for(int i=0;i<arc_da_stampare;i++)
	{
		int j;
		int x = i+(pag-1)*13;
		gotoxy(1,7+i);printf("%03d - ",lista[x].codice);
		j=0;
		while(mat[j].codice != lista[x].materia) j++;
		cout<<mat[j].nome[0]<<mat[j].nome[1]<<mat[j].nome[2];
		cout<<" - ";
		j=0;
		while(aln[j].codice != lista[x].alunno) j++;
		cout<<aln[j].nominativo[0]<<"/";
		int p = trova_car(aln[j].nominativo,'/');
		cout<<aln[j].nominativo[p+1];
		cout<<" - "<<lista[x].voto;
	}
}

int menu_interattivo_alunni()
{
	clear(24,3,56,21);
	colore("ROSSO");
	centra("ALUNNI",3);
	colore("NERO");
	int tasto,riga_partenza = 6;
	char opzioni[4][20] = {"AGGIUNGI","MODIFICA","ELIMINA","INDIETRO"};
	bool opzioni_abilitate[4] = {true,true,true,true};
	for(int i=0;i<4;i++)
		centra(opzioni[i],6+i);
	colore("GIALLO");
	centra(opzioni[0],6);
	colore("NERO");
	int scelta=0;
	do{
		int next = -1,back = -1;
		if(scelta > 0)
		for(int i=scelta-1;i>=0 && back == -1;i--)
		{
			if(opzioni_abilitate[i])
				back = i;
		}
		if(scelta < 4)
		for(int i=scelta+1;i<4 && next == -1;i++)
		{
			if(opzioni_abilitate[i])
				next = i;
		}
		gotoxy(0,0);tasto = getch();
		switch(tasto)
		{
			case 72:if(back != -1)
					{
						colore("NERO");
						centra(opzioni[scelta],riga_partenza+scelta);
						scelta = back;
						colore("GIALLO");
						centra(opzioni[scelta],riga_partenza+scelta);
					}
					break;
			case 80:if(next != -1)
					{
						colore("NERO");
						centra(opzioni[scelta],riga_partenza+scelta);
						scelta = next;
						colore("GIALLO");
						centra(opzioni[scelta],riga_partenza+scelta);
					}
					break;
			case 73:colore("NERO");return -1;
			case 81:colore("NERO");return -2;	
		}
	}while(tasto != 13);
	colore("NERO");
	return scelta+1;
}

int menu_interattivo_interrogazioni()
{
	clear(24,3,56,21);
	colore("ROSSO");
	centra("INTERROGAZIONI",3);
	colore("NERO");
	int tasto,riga_partenza = 6;
	char opzioni[4][20] = {"AGGIUNGI","MODIFICA","ELIMINA","INDIETRO"};
	bool opzioni_abilitate[4] = {true,true,true,true};
	for(int i=0;i<4;i++)
		centra(opzioni[i],6+i);
	colore("GIALLO");
	centra(opzioni[0],6);
	colore("NERO");
	int scelta=0;
	do{
		int next = -1,back = -1;
		if(scelta > 0)
		for(int i=scelta-1;i>=0 && back == -1;i--)
		{
			if(opzioni_abilitate[i])
				back = i;
		}
		if(scelta < 4)
		for(int i=scelta+1;i<4 && next == -1;i++)
		{
			if(opzioni_abilitate[i])
				next = i;
		}
		gotoxy(0,0);tasto = getch();
		switch(tasto)
		{
			case 72:if(back != -1)
					{
						colore("NERO");
						centra(opzioni[scelta],riga_partenza+scelta);
						scelta = back;
						colore("GIALLO");
						centra(opzioni[scelta],riga_partenza+scelta);
					}
					break;
			case 80:if(next != -1)
					{
						colore("NERO");
						centra(opzioni[scelta],riga_partenza+scelta);
						scelta = next;
						colore("GIALLO");
						centra(opzioni[scelta],riga_partenza+scelta);
					}
					break;
			case 73:colore("NERO");return -1;
			case 81:colore("NERO");return -2;	
		}
	}while(tasto != 13);
	colore("NERO");
	return scelta+1;
}

void stampa_tabella_risultati()
{
	clear(0,3,79,21);
	gotoxy(23,2);cout<<(char)196;
	gotoxy(57,2);cout<<(char)196;
	gotoxy(23,22);cout<<(char)196;
	gotoxy(57,22);cout<<(char)196;
	stampa_cornice(0,3,79,21,"");
	gotoxy(3,3);cout<<(char)194;
	gotoxy(22,3);cout<<(char)194;
	gotoxy(31,3);cout<<(char)194;
	gotoxy(40,3);cout<<(char)194;
	gotoxy(49,3);cout<<(char)194;
	gotoxy(58,3);cout<<(char)194;
	gotoxy(67,3);cout<<(char)194;
	gotoxy(73,3);cout<<(char)194;
	gotoxy(3,21);cout<<(char)193;
	gotoxy(22,21);cout<<(char)193;
	gotoxy(31,21);cout<<(char)193;
	gotoxy(40,21);cout<<(char)193;
	gotoxy(49,21);cout<<(char)193;
	gotoxy(58,21);cout<<(char)193;
	gotoxy(67,21);cout<<(char)193;
	gotoxy(73,21);cout<<(char)193;
	for(int i=4;i<21;i++)
	{
		gotoxy(3,i);cout<<(char)179;
		gotoxy(22,i);cout<<(char)179;
		gotoxy(31,i);cout<<(char)179;
		gotoxy(40,i);cout<<(char)179;
		gotoxy(49,i);cout<<(char)179;
		gotoxy(58,i);cout<<(char)179;
		gotoxy(67,i);cout<<(char)179;
		gotoxy(73,i);cout<<(char)179;
	}
	for(int i=1;i<79;i++)
	{
		for(int j=7;j<21;j+=2)
		{
			gotoxy(i,j);cout<<(char)196;
		}
	}
	for(int i=7;i<21;i+=2)
	{
		gotoxy(0,i);cout<<(char)195;
		gotoxy(79,i);cout<<(char)180;
		gotoxy(3,i);cout<<(char)197;
		gotoxy(22,i);cout<<(char)197;
		gotoxy(31,i);cout<<(char)197;
		gotoxy(40,i);cout<<(char)197;
		gotoxy(49,i);cout<<(char)197;
		gotoxy(58,i);cout<<(char)197;
		gotoxy(67,i);cout<<(char)197;
		gotoxy(73,i);cout<<(char)197;
	}
	for(int i=23;i<67;i++)
	{
		gotoxy(i,5);cout<<(char)196;
	}
	gotoxy(22,5);cout<<(char)195;
	gotoxy(67,5);cout<<(char)180;
	gotoxy(31,5);cout<<(char)197;
	gotoxy(40,5);cout<<(char)197;
	gotoxy(49,5);cout<<(char)197;
	gotoxy(58,5);cout<<(char)197;
	gotoxy(25,5);cout<<(char)194;
	gotoxy(25,21);cout<<(char)193;
	gotoxy(28,5);cout<<(char)194;
	gotoxy(28,21);cout<<(char)193;
	gotoxy(34,5);cout<<(char)194;
	gotoxy(34,21);cout<<(char)193;
	gotoxy(37,5);cout<<(char)194;
	gotoxy(37,21);cout<<(char)193;
	gotoxy(43,5);cout<<(char)194;
	gotoxy(43,21);cout<<(char)193;
	gotoxy(46,5);cout<<(char)194;
	gotoxy(46,21);cout<<(char)193;
	gotoxy(52,5);cout<<(char)194;
	gotoxy(52,21);cout<<(char)193;
	gotoxy(55,5);cout<<(char)194;
	gotoxy(55,21);cout<<(char)193;
	gotoxy(61,5);cout<<(char)194;
	gotoxy(61,21);cout<<(char)193;
	gotoxy(64,5);cout<<(char)194;
	gotoxy(64,21);cout<<(char)193;
	for(int i=25;i<65;i+=3)
	{
		for(int j=6;j<21;j++)
		{
			gotoxy(i,j);cout<<(char)179;
		}
		for(int j=7;j<21;j+=2)
		{
			gotoxy(i,j);cout<<(char)197;
		}
	}
	gotoxy(1,4);cout<<"No";
	gotoxy(4,4);cout<<"   NOMINATIVO";
	gotoxy(68,4);cout<<"MEDIA";
	gotoxy(74,4);cout<<"ESITO";
}



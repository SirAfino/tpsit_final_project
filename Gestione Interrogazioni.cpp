#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdio.h>
#include <io.h>
#include "funzioni_avanzate.cpp"
using namespace std;

FILE *archivio;
FILE *appoggio;

struttura_classe classe;
struttura_materia materie[50];
struttura_alunno alunni[99];
struttura_ambito ambiti[3];
struttura_interrogazione interrogazioni[999];
int n_materie,n_alunni,n_interrogazioni;

char nome_archivio[20];
char archivio_classe[50];
char archivio_materie[50];
char archivio_alunni[50];
char archivio_interrogazioni[50];
char archivio_ambiti[50];

bool archivio_set,dati_set,interr_set;
int scelta;

void menu_principale();
void selezione_archivio();
void imposta_dati_classe();
void menu_materie();
void menu_alunni();
void menu_interrogazioni();
void risultati();
void riempi_tabella(int pagx,int pagy);

int main()
{
	ambiti[0].codice = 1;
	strcpy(ambiti[0].nome,"SCRITTO");
	ambiti[1].codice = 2;
	strcpy(ambiti[0].nome,"ORALE");
	ambiti[2].codice = 3;
	strcpy(ambiti[0].nome,"PRATICO");
	do{
		stampa_struttura();
		menu_principale();
		switch(scelta)
		{
			case 1:selezione_archivio();break;
			case 2:imposta_dati_classe();break;
			case 3:menu_materie();break;
			case 4:menu_alunni();break;
			case 5:menu_interrogazioni();break;
			case 6:risultati();break;
		}
	}while(scelta != 7);
}

void menu_principale()
{
	stampa_aiuto("SELEZIONA UN'OPZIONE","TRA LE DISPONIBILI");
	clear(26,23,54,24);
	gotoxy(27,23);cout<<"FRECCIA SU/GIU - SCORRI";
	gotoxy(27,24);cout<<"INVIO - SELEZIONA";
	colore("ROSSO");
	centra("MENU' PRINCIPALE'",3);
	colore("NERO");
	gotoxy(1,5);cout<<"DATI DI LAVORO";
	if(archivio_set)
	{
		gotoxy(2,7);cout<<"ARCHIVIO";
		gotoxy(3,8);cout<<nome_archivio;
	}
	if(dati_set)
	{
		archivio = fopen(archivio_materie,"r+");
		fseek(archivio,0,2);
		n_materie = ftell(archivio) / sizeof(materie[0]);
		fclose(archivio);
		archivio = fopen(archivio_alunni,"r+");
		fseek(archivio,0,2);
		n_alunni = ftell(archivio) / sizeof(alunni[0]);
		fclose(archivio);
		archivio = fopen(archivio_interrogazioni,"r+");
		fseek(archivio,0,2);
		n_interrogazioni = ftell(archivio) / sizeof(interrogazioni[0]);
		fclose(archivio);
		if(n_materie>0 && n_alunni>0)
			interr_set = true;
		else
			interr_set = false;
		gotoxy(2,9);cout<<"NOME SCUOLA";
		gotoxy(3,10);cout<<classe.nome_scuola;
		gotoxy(2,11);cout<<"NOME CLASSE";
		gotoxy(3,12);cout<<classe.nome_classe;
		gotoxy(2,13);cout<<"RANGE VOTI";
		gotoxy(3,14);cout<<classe.voto_min<<"-"<<classe.voto_max<<"("<<classe.voto_suff<<")";
		gotoxy(2,15);cout<<"NUMERO MATERIE";
		gotoxy(3,16);cout<<n_materie;
		gotoxy(2,17);cout<<"NUMERO ALUNNI";
		gotoxy(3,18);cout<<n_alunni;
		gotoxy(2,19);cout<<"NUMERO INTERROGAZIONI";
		gotoxy(3,20);cout<<n_interrogazioni;
	}
	scelta = menu_interattivo_principale(archivio_set,dati_set,interr_set);
}

void selezione_archivio()
{
	stampa_struttura();
	colore("NERO");
	char arc_presenti[100][20];
	archivio = fopen("archivi/lista.txt","r+");
	fseek(archivio,0,2);
	int n_arc = ftell(archivio) / 20;
	int pag = 1;
	int n_pag = n_arc/13;
	if(n_arc%13 != 0)
		n_pag++;
	if(n_pag == 0)
		pag = 0;
	fseek(archivio,0,0);
	for(int i=0;i<n_arc;i++)
	{
		fread(&arc_presenti[i],sizeof(nome_archivio),1,archivio);
	}
	do{
		stampa_aiuto("SELEZIONA UN'OPZIONE","TRA LE DISPONIBILI");
		clear(26,23,54,24);
		gotoxy(27,23);cout<<"FRECCIA SU/GIU - SCORRI";
		gotoxy(27,24);cout<<"INVIO - SELEZIONA";
		stampa_lista_archivi(arc_presenti,pag,n_arc);
		scelta = menu_interattivo_archivi();
		switch(scelta)
		{
			case 1:{colore("NERO");
			       clear(24,3,56,21);
			       stampa_aiuto("INSERISCI IL NOME","DELL'ARCHIVIO");
			       clear(26,23,54,24);
			       gotoxy(27,23);cout<<"A-Z/0-9 - SCRIVI";
				   gotoxy(27,24);cout<<"INVIO - CONFERMA";
			       colore("ROSSO");
				   centra("CREA/SELEZIONA ARCHIVIO",3);
			       colore("NERO");
			       centra("NOME ARCHIVIO",5);
			       stampa_text_box(7,20);
			       char nome[20];
			       int tasto;
			       int n_let = 0;
			       char accettabili[] = "abcdefghilmnopqrstuvzxwykj0123456789 _";
			       do{
			       	 gotoxy(30+n_let,7);
			       	 tasto = getch();
			       	 char lettera = tasto;
			       	 if(trova_car(accettabili,lettera) != -1 && n_let < 20)
			       	 {
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	nome[n_let] = lettera;
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(30+n_let,7);
					 	cout<<" ";
					 }
					 if(lettera == 73 && pag>1)
					 {
					    pag--;
					 	stampa_lista_archivi(arc_presenti,pag,n_arc);
					 }
					 if(lettera == 81 && pag<n_pag)
					{
					    pag++;
					 	stampa_lista_archivi(arc_presenti,pag,n_arc);
					}
					if(tasto == 13 && n_let<3)
						stampa_errore("NOME ARCHIVIO","TROPPO CORTO!");
				   }while(tasto != 13 || n_let<3);
				   clear_errore();
				   nome[n_let] = '\0';
				   bool esiste = false;
				   for(int i=0;i<n_arc;i++)
				   		if(strcmp(arc_presenti[i],nome) == 0)
				   			esiste = true;
				   if(esiste)
				   {
				   	 centra("ARCHIVIO SELEZIONATO",9);
				   	 centra("CORRETTAMENTE!",10);
				   	 stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
				   	 clear(26,23,54,24);
				   	 getch();
				   	 strcpy(nome_archivio,nome);
				   	 crea_nomi_archivi(nome_archivio,archivio_materie,archivio_alunni,archivio_classe,archivio_interrogazioni,archivio_ambiti);
				   	 archivio_set = true;
				   	 archivio = fopen(archivio_classe,"r+");
				   	 fseek(archivio,0,2);
				   	 if(ftell(archivio)>0)
				   	 {
				   	 	dati_set = true;
				   	 	archivio = fopen(archivio_classe,"r+");
				   	 	fread(&classe,sizeof(classe),1,archivio);
				   	 	fclose(archivio);
					 }
				   	 fclose(archivio);
				   }
				   else
				   {
				   	 stampa_aiuto("SELEZIONA UN'OPZIONE","TRA LE DISPONIBILI");
				   	 clear(26,23,54,24);
						gotoxy(27,23);cout<<"FRECCIA SU/GIU - SCORRI";
						gotoxy(27,24);cout<<"INVIO - SELEZIONA";
				   	 centra("ARCHIVIO NON ESISTENTE!",9);
				   	 centra("CREARE L'ARCHIVIO?",10);
				   	 centra("NO",12);
				   	 colore("GIALLO");
				   	 centra("SI",11);
				   	 int tasto;
				   	 int scelta = 1;
				   	 do{
				   	 	colore("NERO");
				   	 	stampa_lista_archivi(arc_presenti,pag,n_arc);
				   	 	gotoxy(0,0);
				   	 	tasto = getch();
				   	 	switch(tasto)
				   	 	{
				   	 		case 72:scelta = 1;
				   	 			    colore("GIALLO");
				   	 			    centra("SI",11);
				   	 			    colore("NERO");
				   	 			    centra("NO",12);break;
				   	 		case 80:scelta = 2;
				   	 			    colore("GIALLO");
				   	 			    centra("NO",12);
				   	 			    colore("NERO");
				   	 			    centra("SI",11);break;
				   	 		case 73:if(pag>1)pag--;break;
				   	 		case 71:if(pag<n_pag)pag++;break;
						}
					 }while(tasto != 13);
					 if(scelta == 1)
					 {
					 	strcpy(nome_archivio,nome);
				   	    crea_nomi_archivi(nome_archivio,archivio_materie,archivio_alunni,archivio_classe,archivio_interrogazioni,archivio_ambiti);
				   	    char cartella[40];
				   	    strcpy(cartella,"archivi/");
				   	    strcat(cartella,nome);
				   	    mkdir(cartella);
				   	    archivio = fopen(archivio_materie,"w");
				   	    fclose(archivio);
				   	    archivio = fopen(archivio_classe,"w");
				   	    fclose(archivio);
				   	    archivio = fopen(archivio_alunni,"w");
				   	    fclose(archivio);
				   	    archivio = fopen(archivio_interrogazioni,"w");
				   	    fclose(archivio);
				   	    archivio = fopen(archivio_ambiti,"w");
				   	    fclose(archivio);
				   	    archivio_set = false;
				   	    dati_set = false;
				   	    strcpy(arc_presenti[n_arc],nome_archivio);
				   	    n_arc++;
				   	    archivio = fopen("archivi/lista.txt","r+");
				   	    fseek(archivio,0,2);
				   	    fwrite(&nome_archivio,sizeof(nome_archivio),1,archivio);
				   	    fclose(archivio);
				   	    stampa_aiuto("SELEZIONA UN'OPZIONE","TRA LE DISPONIBILI");
				   	    clear(26,23,54,24);
						gotoxy(27,23);cout<<"FRECCIA SU/GIU - SCORRI";
						gotoxy(27,24);cout<<"INVIO - SELEZIONA";
				   	    centra("SELEZIONARE L'ARCHIVIO?",14);
				   	    centra("NO",16);
					   	 colore("GIALLO");
					   	 centra("SI",15);
					   	 scelta = 1;
					   	 do{
					   	 	colore("NERO");
					   	 	if(pag == 0)pag++;
					   	 	stampa_lista_archivi(arc_presenti,pag,n_arc);
					   	 	gotoxy(0,0);
					   	 	tasto = getch();
					   	 	switch(tasto)
					   	 	{
					   	 		case 72:scelta = 1;
					   	 			    colore("GIALLO");
					   	 			    centra("SI",15);
					   	 			    colore("NERO");
					   	 			    centra("NO",16);break;
					   	 		case 80:scelta = 2;
					   	 			    colore("GIALLO");
					   	 			    centra("NO",16);
					   	 			    colore("NERO");
					   	 			    centra("SI",15);break;
					   	 		case 73:if(pag>1)pag--;break;
					   	 		case 71:if(pag<n_pag)pag++;break;
							}
					 }while(tasto != 13);
					 if(scelta == 1)
					 	archivio_set = true;
					 }
				   }
				   break;}
				   
			case 2:{colore("NERO");
			       clear(24,3,56,21);
			       colore("ROSSO");
				   centra("ELIMINA ARCHIVIO",3);
			       colore("NERO");
			       centra("NOME ARCHIVIO",5);
			       stampa_text_box(7,20);
			       char nome[20];
			       int tasto;
			       int n_let = 0;
			       stampa_aiuto("INSERISCI IL NOME","DELL'ARCHIVIO");
			       clear(26,23,54,24);
			       gotoxy(27,23);cout<<"A-Z/0-9 - SCRIVI";
				   gotoxy(27,24);cout<<"INVIO - CONFERMA";
			       char accettabili[] = "abcdefghilmnopqrstuvzxwykj0123456789 _";
			       do{
			       	stampa_lista_archivi(arc_presenti,pag,n_arc);
			       	 gotoxy(30+n_let,7);
			       	 tasto = getch();
			       	 char lettera = tasto;
			       	 if(trova_car(accettabili,lettera) != -1 && n_let < 20)
			       	 {
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	nome[n_let] = lettera;
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(30+n_let,7);
					 	cout<<" ";
					 }
					 if(lettera == 73 && pag>1)
						pag--;
					 if(lettera == 81 && pag<n_pag)
						pag++;
					 if(tasto == 13 && n_let<3)
					 	stampa_errore("NOME ARCHIVIO","TROPPO CORTO!");
				   }while(tasto != 13 || n_let<3);
				   clear_errore();
				   nome[n_let] = '\0';
				   bool esiste = false;
				   for(int i=0;i<n_arc;i++)
				   		if(strcmp(arc_presenti[i],nome) == 0)
				   			esiste = true;
				   	if(!esiste)
				   	{
				   		centra("ARCHIVIO NON TROVATO!",10);
				   		stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
				   		getch();
					}
					if(esiste)
				   	{
				   		stampa_aiuto("SELEZIONA UN'OPZIONE","TRA LE DISPONIBILI");
				   		clear(26,23,54,24);
						gotoxy(27,23);cout<<"FRECCIA SU/GIU - SCORRI";
						gotoxy(27,24);cout<<"INVIO - SELEZIONA";
				   	    centra("ELIMINARE L'ARCHIVIO?",10);
				   	    centra("NO",12);
					   	colore("GIALLO");
					   	centra("SI",11);
					   	scelta = 1;
					   	do{
					   	    colore("NERO");
					   	 	gotoxy(0,0);
					   	 	tasto = getch();
					   	 	switch(tasto)
					   	 	{
					   	 		case 72:scelta = 1;
					   	 			    colore("GIALLO");
					   	 			    centra("SI",11);
					   	 			    colore("NERO");
					   	 			    centra("NO",12);break;
					   	 		case 80:scelta = 2;
					   	 			    colore("GIALLO");
					   	 			    centra("NO",12);
					   	 			    colore("NERO");
					   	 			    centra("SI",11);break;
					   	 		case 73:if(pag>1)pag--;break;
					   	 		case 71:if(pag<n_pag)pag++;break;
							}
					 }while(tasto != 13);
					 if(scelta == 1)
			       	{
				   		strcpy(nome_archivio,nome);
				   	    crea_nomi_archivi(nome_archivio,archivio_materie,archivio_alunni,archivio_classe,archivio_interrogazioni,archivio_ambiti);
				   	    remove(archivio_materie);
				   	    remove(archivio_alunni);
				   	    remove(archivio_classe);
				   	    remove(archivio_interrogazioni);
				   	    remove(archivio_ambiti);
						char cartella[40];
				   	    strcpy(cartella,"archivi/");
				   	    strcat(cartella,nome);
				   	    rmdir(cartella);
				   	    archivio_set = false;
				   	    dati_set = false;
				   	    archivio = fopen("archivi/lista.txt","w");
				   	    for(int i=0;i<n_arc;i++)
				   	    {
				   	    	if(strcmp(arc_presenti[i],nome) != 0)
				   	    	  fwrite(&arc_presenti[i],sizeof(arc_presenti[i]),1,archivio);
						}
				   	    fclose(archivio);
				   	    archivio = fopen("archivi/lista.txt","r+");
						fseek(archivio,0,2);
						n_arc = ftell(archivio) / 20;
						pag = 1;
						n_pag = n_arc/13;
						if(n_arc%13 != 0)
							n_pag++;
						if(n_pag == 0)
							pag = 0;
						fseek(archivio,0,0);
						for(int i=0;i<n_arc;i++)
						{
							fread(&arc_presenti[i],sizeof(nome_archivio),1,archivio);
						}
					}
				}
			
			break;}
			case -1:if(pag>1)pag--;break;
			case -2:if(pag<n_pag)pag++;break;
		}
	}while(scelta != 3);
}

void imposta_dati_classe()
{
	stampa_struttura();
	colore("ROSSO");
	centra("MENU' DATI CLASSE",3);
	colore("NERO");
	if(dati_set)
	{
		centra("NOME SCUOLA",5);
		centra(classe.nome_scuola,6);
		centra("NOME CLASSE",8);
		centra(classe.nome_classe,9);
		centra("RANGE VOTI",11);
		char aus[10];
		char vot[16];
		int_string(classe.voto_min,aus);
		strcpy(vot,aus);
		strcat(vot,"-");
		int_string(classe.voto_max,aus);
		strcat(vot,aus);
		strcat(vot,"(");
		int_string(classe.voto_suff,aus);
		strcat(vot,aus);
		strcat(vot,")");
		centra(vot,12);
		stampa_aiuto("SELEZIONA UN'OPZIONE","TRA LE DISPONIBILI");
		clear(26,23,54,24);
gotoxy(27,23);cout<<"FRECCIA SU/GIU - SCORRI";
gotoxy(27,24);cout<<"INVIO - SELEZIONA";
		centra("MODIFICARE I DATI?",14);
		centra("NO",16);
	    colore("GIALLO");
		centra("SI",15);
		int tasto;
		int scelta = 1;
		do{
			colore("NERO");
			gotoxy(0,0);
			tasto = getch();
			switch(tasto)
				{
				case 72:scelta = 1;
				   	 	colore("GIALLO");
				   	 	centra("SI",15);
				   	 	colore("NERO");
				   	 	centra("NO",16);break;
				case 80:scelta = 2;
				   	 	colore("GIALLO");
				   	 	centra("NO",16);
				   	 	colore("NERO");
				   	 	centra("SI",15);break;
			}
		}while(tasto != 13);
		if(scelta == 1)
		{
			clear(0,3,22,21);
			colore("ROSSO");
			stampa_distanza("HELP IN LINEA",3,4,'s');
			colore("NERO");
			gotoxy(1,5);cout<<"DATI CLASSE";
			gotoxy(2,7);cout<<"NOME SCUOLA:";
			scrivi(classe.nome_scuola,3,8,21);
			gotoxy(2,10);cout<<"NOME CLASSE:";
			scrivi(classe.nome_classe,3,11,21);
			gotoxy(2,13);cout<<"RANGE VOTI:";
			scrivi(vot,3,14,21);
		}
		if(scelta == 2)
			return;
	}
	clear(24,4,56,21);
	centra("NOME SCUOLA",5);
	stampa_text_box(7,20);
	centra("NOME CLASSE",9);
	stampa_text_box(11,20);
	stampa_aiuto("INSERISCI IL NOME","DELLA SCUOLA");
	clear(26,23,54,24);
gotoxy(27,23);cout<<"A-Z/0-9 - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
	char nome[20];
	int tasto;
	int n_let = 0;
	char accettabili[] = "abcdefghilmnopqrstuvzxwykj0123456789 _.";
	do{
		gotoxy(30+n_let,7);
		tasto = getch();
	    char lettera = tasto;
	    if(trova_car(accettabili,lettera) != -1 && n_let < 20)
		{
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	nome[n_let] = lettera;
			       	 	n_let++;
		}
		if(lettera == 8 && n_let>0)
		{
					 	n_let--;
					 	gotoxy(30+n_let,7);
					 	cout<<" ";
		}
		if(tasto == 13 && n_let<3)
			stampa_errore("NOME SCUOLA","TROPPO CORTO!");
	}while(tasto != 13 || n_let<3);
	clear_errore();
	nome[n_let] = '\0';
	strcpy(classe.nome_scuola,nome);
	n_let = 0;
	stampa_aiuto("INSERISCI IL NOME","DELLA CLASSE");
	clear(26,23,54,24);
gotoxy(27,23);cout<<"A-Z/0-9 - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
	do{
		gotoxy(30+n_let,11);
		tasto = getch();
	    char lettera = tasto;
	    if(trova_car(accettabili,lettera) != -1 && n_let < 20)
		{
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	nome[n_let] = lettera;
			       	 	n_let++;
		}
		if(lettera == 8 && n_let>0)
		{
					 	n_let--;
					 	gotoxy(30+n_let,7);
					 	cout<<" ";
		}
		if(tasto == 13 && n_let<2)
		stampa_errore("NOME CLASSE","TROPPO CORTO!");
	}while(tasto != 13 || n_let<2);
	nome[n_let] = '\0';
	strcpy(classe.nome_classe,nome);
	clear(24,4,56,21);
	centra("  VOTO MINIMO",5);
	stampa_text_box(7,3);
	centra("  VOTO MASSIMO",9);
	stampa_text_box(11,3);
	centra("   VOTO SUFFICIENZA",13);
	stampa_text_box(15,3);
	gotoxy(39,7);printf("%03d",classe.voto_min);
	gotoxy(39,11);printf("%03d",classe.voto_max);
	if(!dati_set)
	{
		stampa_aiuto("INSERISCI IL","VOTO MINIMO");
		clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
		gotoxy(39,7);cout<<"   ";
		gotoxy(39,11);cout<<"   ";
		char acc[] = "0123456789";
		int n = 0;
		n_let = 0;
		do{
			gotoxy(39+n_let,7);
			tasto = getch();
		    char lettera = tasto;
		    if(trova_car(acc,lettera) != -1 && n_let < 3)
			{
				       	 	converti_car(lettera);
				       	 	cout<<lettera;
				       	 	n*=10;
				       	 	n+=lettera-'0';
				       	 	n_let++;
			}
			if(lettera == 8 && n_let>0)
			{
						 	n_let--;
						 	n/=10;
						 	gotoxy(39+n_let,7);
						 	cout<<" ";
			}
			if(tasto == 13 && (n_let<1 || n<0))
		stampa_errore("VOTO MINIMO","NON VALIDO!");
		}while(tasto != 13 || n_let<1 || n<0);
		clear_errore();
		classe.voto_min = n;
		n = 0;
		n_let = 0;
		stampa_aiuto("INSERISCI IL","VOTO MASSIMO");
		clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
		do{
			gotoxy(39+n_let,11);
			tasto = getch();
		    char lettera = tasto;
		    if(trova_car(acc,lettera) != -1 && n_let < 3)
			{
				       	 	converti_car(lettera);
				       	 	cout<<lettera;
				       	 	n*=10;
				       	 	n+=lettera-'0';
				       	 	n_let++;
			}
			if(lettera == 8 && n_let>0)
			{
						 	n_let--;
						 	n/=10;
						 	gotoxy(39+n_let,11);
						 	cout<<" ";
			}
			if(tasto == 13 && (n_let<1 || n<classe.voto_min+3))
		stampa_errore("VOTO MASSIMO","NON VALIDO!");
		}while(tasto != 13 || n_let<1 || n<classe.voto_min+3);
		clear_errore();
		classe.voto_max = n;
	}
	
	stampa_aiuto("INSERISCI IL","VOTO SUFFICIENZA");
	clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
	char acc[] = "0123456789";
	int n = 0;
	n_let = 0;
	do{
		gotoxy(39+n_let,15);
		tasto = getch();
	    char lettera = tasto;
	    if(trova_car(acc,lettera) != -1 && n_let < 3)
		{
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	n*=10;
			       	 	n+=lettera-'0';
			       	 	n_let++;
		}
		if(lettera == 8 && n_let>0)
		{
					 	n_let--;
					 	n/=10;
					 	gotoxy(39+n_let,15);
					 	cout<<" ";
		}
		if(tasto == 13 && (n_let<1 || n<=classe.voto_min || n>=classe.voto_max))
		stampa_errore("VOTO SUFFICIENZA","NON VALIDO!");
	}while(tasto != 13 || n_let<1 || n<=classe.voto_min || n>=classe.voto_max);
	clear_errore();
	classe.voto_suff = n;
	dati_set = true;
	archivio = fopen(archivio_classe,"w");
	fwrite(&classe,sizeof(classe),1,archivio);
	fclose(archivio);
}

void menu_materie()
{
	stampa_struttura();
	colore("NERO");
	archivio = fopen(archivio_materie,"r+");
	fseek(archivio,0,2);
	int n_mat = ftell(archivio) / sizeof(materie[0]);
	int pag = 1;
	int n_pag = n_mat/13;
	if(n_mat%13 != 0)
		n_pag++;
	if(n_pag == 0)
		pag = 0;
	fseek(archivio,0,0);
	for(int i=0;i<n_mat;i++)
	{
		fread(&materie[i],sizeof(materie[i]),1,archivio);
	}
	do{
		n_pag = n_mat/13;
		if(n_mat%13 != 0)
			n_pag++;
        if(pag>n_pag)
           pag = n_pag;
        stampa_aiuto("SELEZIONA UN'OPZIONE","TRA LE DISPONIBILI");
        clear(26,23,54,24);
gotoxy(27,23);cout<<"FRECCIA SU/GIU - SCORRI";
gotoxy(27,24);cout<<"INVIO - SELEZIONA";
		stampa_lista_materie(materie,pag,n_mat);
		scelta = menu_interattivo_materie();
		switch(scelta)
		{        
            case -1:{
                 if(pag>1)pag--;
                 break;}          
            case -2:{
                 if(pag<n_pag)pag++;
                 break;}         
			case 1:{
				colore("NERO");
			    clear(24,3,56,21);
			    colore("ROSSO");
				centra("AGGIUNGI MATERIA",3);
			    colore("NERO");
			    centra("NOME MATERIA",5);
			    stampa_text_box(7,20);
			    char nome[20];
			    int tasto;
			    int n_let = 0;
			    stampa_aiuto("INSERISCI IL NOME","DELLA MATERIA");
			    clear(26,23,54,24);
				gotoxy(27,23);cout<<"A-Z/0-9 - SCRIVI";
				gotoxy(27,24);cout<<"INVIO - CONFERMA";
			    char accettabili[] = "abcdefghilmnopqrstuvzxwykj0123456789 ";
			    do{
			       	 gotoxy(30+n_let,7);
			       	 tasto = getch();
			       	 char lettera = tasto;
			       	 if(trova_car(accettabili,lettera) != -1 && n_let < 20)
			       	 {
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	nome[n_let] = lettera;
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(30+n_let,7);
					 	cout<<" ";
					 }
					 if(lettera == 73 && pag>1)
					 {
					    pag--;
					 	stampa_lista_materie(materie,pag,n_mat);
					 }
					 if(lettera == 81 && pag<n_pag)
					{
					    pag++;
					 	stampa_lista_materie(materie,pag,n_mat);
					}
					if(tasto == 13 && n_let<3)
		stampa_errore("NOME MATERIA","TROPPO CORTO!");
				   }while(tasto != 13 || n_let<3);
				   clear_errore();
				   nome[n_let] = '\0';
				   bool esiste = false;
				   for(int i=0;i<n_mat;i++)
				   		if(strcmp(materie[i].nome,nome) == 0)
				   			esiste = true;
				   	if(esiste)
				   	{
				   		centra("LA MATERIA ESISTE GIA'!",10);
				   		stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
				   		clear(26,23,54,24);
				   		getch();
					}
					else
					{
						centra("MATERIA AGGIUNTA",10);
						centra("CORRETTAMENTE!",11);
						clear(26,23,54,24);
						stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
						materie[n_mat].codice = materie[n_mat-1].codice + 1;
						strcpy(materie[n_mat].nome,nome);
						archivio = fopen(archivio_materie,"r+");
						fseek(archivio,0,2);
						fwrite(&materie[n_mat],sizeof(materie[0]),1,archivio);
						fclose(archivio);
						n_mat++;
						if(pag == 0)pag++;
						stampa_lista_materie(materie,pag,n_mat);
						getch();
					}
				break;
			}
			case 2:{
				colore("NERO");
			    clear(24,3,56,21);
			    colore("ROSSO");
				centra("MODIFICA MATERIA",3);
			    colore("NERO");
			    centra("CODICE MATERIA",5);
			    stampa_text_box(7,2);
			    int codice = 0;
			    int tasto;
			    int n_let = 0;
			    stampa_aiuto("INSERISCI IL CODICE","DELLA MATERIA");
				gotoxy(27,23);cout<<"0-9 - SCRIVI";
				gotoxy(27,24);cout<<"INVIO - CONFERMA";
			    char accettabili[] = "0123456789";
			    do{
			       	 gotoxy(39+n_let,7);
			       	 tasto = getch();
			       	 char lettera = tasto;
			       	 if(trova_car(accettabili,lettera) != -1 && n_let < 2)
			       	 {
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	codice*=10;
			       	 	codice+=lettera - '0';
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	codice/=10;
					 	gotoxy(39+n_let,7);
					 	cout<<" ";
					 }
					 if(lettera == 73 && pag>1)
					 {
					    pag--;
					 	stampa_lista_materie(materie,pag,n_mat);
					 }
					 if(lettera == 81 && pag<n_pag)
					{
					    pag++;
					 	stampa_lista_materie(materie,pag,n_mat);
					}
					if(tasto == 13 && n_let<1)
					stampa_errore("CODICE MATERIA","TROPPO CORTO!");
				   }while(tasto != 13 || n_let<1);
				   clear_errore();
				   bool esiste = false;
				   for(int i=0;i<n_mat;i++)
				   		if(materie[i].codice == codice)
				   			esiste = true;
				   	if(!esiste)
				   	{
				   		centra("MATERIA NON TROVATA!",10);
				   		stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
				   		clear(26,23,54,24);
				   		getch();
					}
					else
					{
					    centra("NOME MATERIA",10);
					    stampa_text_box(12,20);
					    char nome[20];
					    int tasto;
					    int n_let = 0;
					    stampa_aiuto("INSERISCI IL NOME","DELLA MATERIA");
					    clear(26,23,54,24);
gotoxy(27,23);cout<<"A-Z/0-9 - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
					    char accettabili[] = "abcdefghilmnopqrstuvzxwykj0123456789 ";
					    do{
					       	 gotoxy(30+n_let,12);
					       	 tasto = getch();
					       	 char lettera = tasto;
					       	 if(trova_car(accettabili,lettera) != -1 && n_let < 20)
					       	 {
					       	 	converti_car(lettera);
					       	 	cout<<lettera;
					       	 	nome[n_let] = lettera;
					       	 	n_let++;
							 }
							 if(lettera == 8 && n_let>0)
							 {
							 	n_let--;
							 	gotoxy(30+n_let,12);
							 	cout<<" ";
							 }
							 if(lettera == 73 && pag>1)
							 {
							    pag--;
							 	stampa_lista_materie(materie,pag,n_mat);
							 }
							 if(lettera == 81 && pag<n_pag)
							{
							    pag++;
							 	stampa_lista_materie(materie,pag,n_mat);
							}
						   }while(tasto != 13 || n_let<3);
						   nome[n_let] = '\0';
						   bool esiste = false;
						   for(int i=0;i<n_mat;i++)
						   		if(strcmp(materie[i].nome,nome) == 0)
						   			esiste = true;
						   	if(esiste)
						   	{
						   		centra("NOME MATERIA",15);
						   		centra("GIA' UTILIZZATO!",16);
						   		stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
						   		clear(26,23,54,24);
						   		getch();
							}
							else
							{
								centra("MATERIA MODIFICATA",15);
						   		centra("CORRETTAMENTE!",16);
						   		stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
						   		clear(26,23,54,24);
						   		int i=0;
						   		while(materie[i].codice != codice)
						   		{i++;}
						   		strcpy(materie[i].nome,nome);
						   		archivio = fopen(archivio_materie,"w");
						   		for(i=0;i<n_mat;i++)
						   			fwrite(&materie[i],sizeof(materie[i]),1,archivio);
						   		fclose(archivio);
						   		stampa_lista_materie(materie,pag,n_mat);
						   		getch();
							}
					}
				break;
			}
			case 3:{
				colore("NERO");
			    clear(24,3,56,21);
			    colore("ROSSO");
				centra("ELIMINA MATERIA",3);
			    colore("NERO");
			    centra("CODICE MATERIA",5);
			    stampa_text_box(7,2);
			    int codice = 0;
			    int tasto;
			    int n_let = 0;
			    stampa_aiuto("INSERISCI IL CODICE","DELLA MATERIA");
			    clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
			    char accettabili[] = "0123456789";
			    do{
			       	 gotoxy(39+n_let,7);
			       	 tasto = getch();
			       	 char lettera = tasto;
			       	 if(trova_car(accettabili,lettera) != -1 && n_let < 2)
			       	 {
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	codice*=10;
			       	 	codice+=lettera - '0';
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	codice/=10;
					 	gotoxy(39+n_let,7);
					 	cout<<" ";
					 }
					 if(lettera == 73 && pag>1)
					 {
					    pag--;
					 	stampa_lista_materie(materie,pag,n_mat);
					 }
					 if(lettera == 81 && pag<n_pag)
					{
					    pag++;
					 	stampa_lista_materie(materie,pag,n_mat);
					}
					if(tasto == 13 && n_let<1)
		stampa_errore("CODICE MATERIA","TROPPO CORTO!");
				   }while(tasto != 13 || n_let<1);
				   clear_errore();
				   bool esiste = false;
				   for(int i=0;i<n_mat;i++)
				   		if(materie[i].codice == codice)
				   			esiste = true;
				   	if(!esiste)
				   	{
				   		centra("MATERIA NON TROVATA!",10);
				   		clear(26,23,54,24);
				   		stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
				   		getch();
					}
					else
					{
						int pos = 0;
						while(materie[pos].codice != codice)
						{pos++;}
					    centra("NOME MATERIA",10);
					    stampa_text_box(12,20);
					    gotoxy(30,12);cout<<materie[pos].nome;
						bool esiste = false;
						stampa_aiuto("SELEZIONA UN'OPZIONE","TRA LE DISPONIBILI");
						clear(26,23,54,24);
						gotoxy(27,23);cout<<"FRECCIA SU/GIU - SCORRI";
						gotoxy(27,24);cout<<"INVIO - SELEZIONA";
						centra("ELIMINARE LA MATERIA?",15);
						centra("NO",17);
					    colore("GIALLO");
						centra("SI",16);
						int tasto;
						int scelta = 1;
						do{
							colore("NERO");
							gotoxy(0,0);
							tasto = getch();
							switch(tasto)
								{
								case 72:scelta = 1;
								   	 	colore("GIALLO");
								   	 	centra("SI",16);
								   	 	colore("NERO");
								   	 	centra("NO",17);break;
								case 80:scelta = 2;
								   	 	colore("GIALLO");
								   	 	centra("NO",17);
								   	 	colore("NERO");
								   	 	centra("SI",16);break;
							}
						}while(tasto != 13);
						if(scelta == 1)
						{
							archivio = fopen(archivio_materie,"w");
						   	for(int i=0;i<n_mat;i++)
						   		if(materie[i].codice != codice)
						   			fwrite(&materie[i],sizeof(materie[i]),1,archivio);
						   	fclose(archivio);
						   	n_mat--;
						   	archivio = fopen(archivio_materie,"r+");
						   	for(int i=0;i<n_mat;i++)
						   			fread(&materie[i],sizeof(materie[i]),1,archivio);
						   	fclose(archivio);
						   	if(n_mat == 0)
						   	 pag = 0;
						   	stampa_lista_materie(materie,pag,n_mat);
						   	archivio = fopen(archivio_interrogazioni,"r+");
						   	for(int i=0;i<n_interrogazioni;i++)
						   		fread(&interrogazioni[i],sizeof(interrogazioni[0]),1,archivio);
						   	fclose(archivio);
						   	archivio = fopen(archivio_interrogazioni,"w");
						   	for(int i=0;i<n_interrogazioni;i++)
						   		if(interrogazioni[i].materia != codice)
								   fwrite(&interrogazioni[i],sizeof(interrogazioni[0]),1,archivio);
						   	fclose(archivio);
						   	centra("MATERIA ELIMINATA!",19);
						   	stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
						   	clear(26,23,54,24);
						   	getch();
						}
					  }
					}
				break;
			}
	}while(scelta != 4);
}

void menu_alunni()
{
	stampa_struttura();
	colore("NERO");
	archivio = fopen(archivio_alunni,"r+");
	fseek(archivio,0,2);
	int n_aln = ftell(archivio) / sizeof(alunni[0]);
	int pag = 1;
	int n_pag = n_aln/13;
	if(n_aln%13 != 0)
		n_pag++;
	if(n_pag == 0)
		pag = 0;
	fseek(archivio,0,0);
	for(int i=0;i<n_aln;i++)
	{
		fread(&alunni[i],sizeof(alunni[i]),1,archivio);
	}
	do{
		n_pag = n_aln/13;
		if(n_aln%13 != 0)
			n_pag++;
		if(pag>n_pag)
			pag = n_pag;
		stampa_lista_alunni(alunni,pag,n_aln);
		stampa_aiuto("SELEZIONA UN'OPZIONE","TRA LE DISPONIBILI");
clear(26,23,54,24);
gotoxy(27,23);cout<<"FRECCIA SU/GIU - SCORRI";
gotoxy(27,24);cout<<"INVIO - SELEZIONA";
		scelta = menu_interattivo_alunni();
		switch(scelta)
		{
			case -1:{
                 if(pag>1)pag--;
                 break;}          
            case -2:{
                 if(pag<n_pag)pag++;
                 break;} 
			case 1:{
				colore("NERO");
			    clear(24,3,56,21);
			    colore("ROSSO");
				centra("AGGIUNGI ALUNNO",3);
			    colore("NERO");
			    centra("NOME ALUNNO",5);
			    stampa_text_box(7,20);
			    centra("  SESSO",10);
			    stampa_text_box(12,1);
			    centra("DATA DI NASCITA",15);
			    stampa_text_box(17,10);
			    char nome[20];
			    int tasto;
			    int n_let = 0;
			    stampa_aiuto("INSERISCI IL NOME","DELL'ALUNNO");
clear(26,23,54,24);
gotoxy(27,23);cout<<"A-Z - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
			    char accettabili[] = "abcdefghilmnopqrstuvzxwykj /";
			    do{
			       	 gotoxy(30+n_let,7);
			       	 tasto = getch();
			       	 char lettera = tasto;
			       	 if(trova_car(accettabili,lettera) != -1 && n_let < 20)
			       	 {
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	nome[n_let] = lettera;
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(30+n_let,7);
					 	cout<<" ";
					 }
					 if(lettera == 73 && pag>1)
					 {
					    pag--;
					 	stampa_lista_alunni(alunni,pag,n_aln);
					 }
					 if(lettera == 81 && pag<n_pag)
					{
					    pag++;
					 	stampa_lista_alunni(alunni,pag,n_aln);
					}
					if(tasto == 13 && !controllo_nominativo(nome))
		stampa_errore("NOME ALUNNO","NON VALIDO!");
				   }while(tasto != 13 || !controllo_nominativo(nome));
				   clear_errore();
				   nome[n_let] = '\0';
				   strcpy(alunni[n_aln].nominativo,nome);
				   nome[0] = '\0';
				   n_let = 0;
				   stampa_aiuto("INSERISCI IL SESSO","DELL'ALUNNO");
clear(26,23,54,24);
gotoxy(27,23);cout<<"M/F - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
			       char acc[] = "fm";
			      do{
			       	 gotoxy(40+n_let,12);
			       	 tasto = getch();
			       	 char lettera = tasto;
			       	 if(trova_car(acc,lettera) != -1 && n_let < 1)
			       	 {
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	alunni[n_aln].sesso = lettera;
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(40+n_let,12);
					 	cout<<" ";
					 }
					 if(lettera == 73 && pag>1)
					 {
					    pag--;
					 	stampa_lista_alunni(alunni,pag,n_aln);
					 }
					 if(lettera == 81 && pag<n_pag)
					{
					    pag++;
					 	stampa_lista_alunni(alunni,pag,n_aln);
					}
					if(tasto == 13 && n_let<1)
		stampa_errore("SESSO ALUNNO","NON VALIDO!");
				   }while(tasto != 13 || n_let<1);
				   clear_errore();
			    n_let = 0;
			    stampa_aiuto("INSERISCI LA DATA","DI NASCITA");
				clear(26,23,54,24);
				gotoxy(27,23);cout<<"0-9 / - SCRIVI";
				gotoxy(27,24);cout<<"INVIO - CONFERMA";
			    char accett[] = "/0123456789";
			    do{
			       	 gotoxy(35+n_let,17);
			       	 tasto = getch();
			       	 char lettera = tasto;
			       	 if(trova_car(accett,lettera) != -1 && n_let < 10)
			       	 {
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	nome[n_let] = lettera;
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(35+n_let,17);
					 	cout<<" ";
					 }
					 if(lettera == 73 && pag>1)
					 {
					    pag--;
					 	stampa_lista_alunni(alunni,pag,n_aln);
					 }
					 if(lettera == 81 && pag<n_pag)
					{
					    pag++;
					 	stampa_lista_alunni(alunni,pag,n_aln);
					}
					nome[n_let] = '\0';
					if(tasto == 13 && !controllo_data(nome))
						stampa_errore("DATA DI NASCITA","NON VALIDA!");
				   }while(tasto != 13 || !controllo_data(nome));
				   clear(26,23,54,24);
				   nome[n_let] = '\0';
				   strcpy(alunni[n_aln].data_nascita,nome);
				   alunni[n_aln].codice = alunni[n_aln-1].codice+1;
				   archivio = fopen(archivio_alunni,"r+");
				   fseek(archivio,0,2);
				   fwrite(&alunni[n_aln],sizeof(alunni[0]),1,archivio);
				   fclose(archivio);
				   n_aln++;
				   if(pag == 0)pag++;
				   centra("  ALUNNO CREATO CORRETTAMENTE!",20);
				   stampa_lista_alunni(alunni,pag,n_aln);
				   stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
				   clear(26,23,54,24);
				   getch();
				break;
			}
			case 2:{
				colore("NERO");
			    clear(24,3,56,21);
			    colore("ROSSO");
				centra("MODIFICA ALUNNO",3);
			    colore("NERO");
			    centra("CODICE ALUNNO",5);
			    stampa_text_box(7,2);
			    int codice = 0;
			    int tasto;
			    int n_let = 0;
			    char accettabili[] = "0123456789";
			    stampa_aiuto("INSERISCI IL CODICE","DELL'ALUNNO");
				clear(26,23,54,24);
				gotoxy(27,23);cout<<"0-9 - SCRIVI";
				gotoxy(27,24);cout<<"INVIO - CONFERMA";
			    do{
			       	 gotoxy(39+n_let,7);
			       	 tasto = getch();
			       	 char lettera = tasto;
			       	 if(trova_car(accettabili,lettera) != -1 && n_let < 2)
			       	 {
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	codice*=10;
			       	 	codice+=lettera - '0';
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	codice/=10;
					 	gotoxy(39+n_let,7);
					 	cout<<" ";
					 }
					 if(lettera == 73 && pag>1)
					 {
					    pag--;
					 	stampa_lista_alunni(alunni,pag,n_aln);
					 }
					 if(lettera == 81 && pag<n_pag)
					{
					    pag++;
					 	stampa_lista_alunni(alunni,pag,n_aln);
					}
					if(tasto == 13 && n_let<1)
		stampa_errore("CODICE ALUNNO","TROPPO CORTO!");
				   }while(tasto != 13 || n_let<1);
				   clear_errore();
				   bool esiste = false;
				   for(int i=0;i<n_aln;i++)
				   		if(alunni[i].codice == codice)
				   			esiste = true;
				   int cod = codice;
				   codice = 0;
				   while(alunni[codice].codice != cod)
				   {codice++;}
				   if(!esiste)
				   	{
				   		centra("ALUNNO NON TROVATO!",10);
				   		stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
				   		clear(26,23,54,24);
				   		getch();
					}
					else
					{
						colore("NERO");
					    clear(24,3,56,21);
					    colore("ROSSO");
						centra("MODIFICA ALUNNO",3);
					    colore("NERO");
					    centra("NOME ALUNNO",5);
					    stampa_text_box(7,20);
					    centra("  SESSO",10);
					    stampa_text_box(12,1);
					    centra("DATA DI NASCITA",15);
					    stampa_text_box(17,10);
					    char nome[20];
					    int tasto;
					    int n_let = 0;
					    stampa_aiuto("INSERISCI IL NOME","DELL'ALUNNO");
clear(26,23,54,24);
gotoxy(27,23);cout<<"A-Z - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
					    char accettabili[] = "abcdefghilmnopqrstuvzxwykj /";
					    do{
					       	 gotoxy(30+n_let,7);
					       	 tasto = getch();
					       	 char lettera = tasto;
					       	 if(trova_car(accettabili,lettera) != -1 && n_let < 20)
					       	 {
					       	 	converti_car(lettera);
					       	 	cout<<lettera;
					       	 	nome[n_let] = lettera;
					       	 	n_let++;
							 }
							 if(lettera == 8 && n_let>0)
							 {
							 	n_let--;
							 	gotoxy(30+n_let,7);
							 	cout<<" ";
							 }
							 if(lettera == 73 && pag>1)
							 {
							    pag--;
							 	stampa_lista_alunni(alunni,pag,n_aln);
							 }
							 if(lettera == 81 && pag<n_pag)
							{
							    pag++;
							 	stampa_lista_alunni(alunni,pag,n_aln);
							}
							if(tasto == 13 && !controllo_nominativo(nome))
		stampa_errore("NOME ALUNNO","NON VALIDO!");
						   }while(tasto != 13 || !controllo_nominativo(nome));
						   clear_errore();
						   nome[n_let] = '\0';
						   strcpy(alunni[codice].nominativo,nome);
						   nome[0] = '\0';
						   n_let = 0;
						   stampa_aiuto("INSERISCI IL SESSO","DELL'ALUNNO");
clear(26,23,54,24);
gotoxy(27,23);cout<<"M/F - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
					       char acc[] = "fm";
					      do{
					       	 gotoxy(40+n_let,12);
					       	 tasto = getch();
					       	 char lettera = tasto;
					       	 if(trova_car(acc,lettera) != -1 && n_let < 1)
					       	 {
					       	 	converti_car(lettera);
					       	 	cout<<lettera;
					       	 	alunni[codice].sesso = lettera;
					       	 	n_let++;
							 }
							 if(lettera == 8 && n_let>0)
							 {
							 	n_let--;
							 	gotoxy(40+n_let,12);
							 	cout<<" ";
							 }
							 if(lettera == 73 && pag>1)
							 {
							    pag--;
							 	stampa_lista_alunni(alunni,pag,n_aln);
							 }
							 if(lettera == 81 && pag<n_pag)
							{
							    pag++;
							 	stampa_lista_alunni(alunni,pag,n_aln);
							}
							if(tasto == 13 && n_let<1)
		stampa_errore("SESSO ALUNNO","NON VALIDO!");
						   }while(tasto != 13 || n_let<1);
						   clear_errore();
					    n_let = 0;
					    stampa_aiuto("INSERISCI LA DATA","DI NASCITA");
				clear(26,23,54,24);
				gotoxy(27,23);cout<<"0-9 / - SCRIVI";
				gotoxy(27,24);cout<<"INVIO - CONFERMA";
					    char accett[] = "/0123456789";
					    do{
					       	 gotoxy(35+n_let,17);
					       	 tasto = getch();
					       	 char lettera = tasto;
					       	 if(trova_car(accett,lettera) != -1 && n_let < 10)
					       	 {
					       	 	converti_car(lettera);
					       	 	cout<<lettera;
					       	 	nome[n_let] = lettera;
					       	 	n_let++;
							 }
							 if(lettera == 8 && n_let>0)
							 {
							 	n_let--;
							 	gotoxy(35+n_let,17);
							 	cout<<" ";
							 }
							 if(lettera == 73 && pag>1)
							 {
							    pag--;
							 	stampa_lista_alunni(alunni,pag,n_aln);
							 }
							 if(lettera == 81 && pag<n_pag)
							{
							    pag++;
							 	stampa_lista_alunni(alunni,pag,n_aln);
							}
							nome[n_let] = '\0';
							if(tasto == 13 && !controllo_data(nome))
						stampa_errore("DATA DI NASCITA","NON VALIDA!");
						   }while(tasto != 13 || !controllo_data(nome));
						   clear_errore();
						   nome[n_let] = '\0';
						   strcpy(alunni[codice].data_nascita,nome);
						   archivio = fopen(archivio_alunni,"r+");
						   fseek(archivio,0,2);
						   for(int i=0;i<n_aln;i++)
						   fwrite(&alunni[i],sizeof(alunni[0]),1,archivio);
						   fclose(archivio);
						   centra("  ALUNNO MOD. CORRETTAMENTE!",20);
						   stampa_lista_alunni(alunni,pag,n_aln);
						   stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
				   clear(26,23,54,24);
						   getch();
					}
				break;
			}
			case 3:{
				colore("NERO");
			    clear(24,3,56,21);
			    colore("ROSSO");
				centra("ELIMINA ALUNNO",3);
			    colore("NERO");
			    centra("CODICE ALUNNO",5);
			    stampa_text_box(7,2);
			    int codice = 0;
			    int tasto;
			    int n_let = 0;
			    stampa_aiuto("INSERISCI IL CODICE","DELL'ALUNNO");
				clear(26,23,54,24);
				gotoxy(27,23);cout<<"0-9 - SCRIVI";
				gotoxy(27,24);cout<<"INVIO - CONFERMA";
			    char accettabili[] = "0123456789";
			    do{
			       	 gotoxy(39+n_let,7);
			       	 tasto = getch();
			       	 char lettera = tasto;
			       	 if(trova_car(accettabili,lettera) != -1 && n_let < 2)
			       	 {
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	codice*=10;
			       	 	codice+=lettera - '0';
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	codice/=10;
					 	gotoxy(39+n_let,7);
					 	cout<<" ";
					 }
					 if(lettera == 73 && pag>1)
					 {
					    pag--;
					 	stampa_lista_alunni(alunni,pag,n_aln);
					 }
					 if(lettera == 81 && pag<n_pag)
					{
					    pag++;
					 	stampa_lista_alunni(alunni,pag,n_aln);
					}
					if(tasto == 13 && n_let<1)
						stampa_errore("CODICE ALUNNO","TROPPO CORTO!");
				   }while(tasto != 13 || n_let<1);
				   clear_errore();
				   bool esiste = false;
				   for(int i=0;i<n_aln;i++)
				   		if(alunni[i].codice == codice)
				   			esiste = true;
				   int cod = codice;
				   codice = 0;
				   while(alunni[codice].codice != cod)
				   {codice++;}
				   if(!esiste)
				   	{
				   		centra("ALUNNO NON TROVATO!",10);
				   		stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
				   		clear(26,23,54,24);
				   		getch();
					}
					else
					{
						colore("NERO");
					    clear(24,3,56,21);
					    colore("ROSSO");
						centra("ELIMINA ALUNNO",3);
					    colore("NERO");
					    centra("NOME ALUNNO",5);
					    stampa_text_box(7,20);
					    centra("  SESSO",9);
					    stampa_text_box(11,1);
					    centra("DATA DI NASCITA",13);
					    stampa_text_box(15,10);
					    gotoxy(30,7);cout<<alunni[codice].nominativo;
					    gotoxy(40,11);cout<<alunni[codice].sesso;
					    gotoxy(35,15);cout<<alunni[codice].data_nascita;
						centra("ELIMINARE L'ALUNNO?",17);
						centra("NO",19);
					    colore("GIALLO");
						centra("SI",18);
						int tasto;
						int scelta = 1;
						stampa_aiuto("SELEZIONA UN'OPZIONE","TRA LE DISPONIBILI");
						clear(26,23,54,24);
						gotoxy(27,23);cout<<"FRECCIA SU/GIU - SCORRI";
						gotoxy(27,24);cout<<"INVIO - SELEZIONA";
						do{
							colore("NERO");
							gotoxy(0,0);
							tasto = getch();
							switch(tasto)
								{
								case 72:scelta = 1;
								   	 	colore("GIALLO");
								   	 	centra("SI",18);
								   	 	colore("NERO");
								   	 	centra("NO",19);break;
								case 80:scelta = 2;
								   	 	colore("GIALLO");
								   	 	centra("NO",19);
								   	 	colore("NERO");
								   	 	centra("SI",18);break;
							}
						}while(tasto != 13);
						if(scelta == 1)
						{
							stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
				   		clear(26,23,54,24);
							centra(" ALUNNO ELIM. CORRETTAMENTE!",20);
							archivio = fopen(archivio_interrogazioni,"r+");
						   	for(int i=0;i<n_interrogazioni;i++)
						   		fread(&interrogazioni[i],sizeof(interrogazioni[0]),1,archivio);
						   	fclose(archivio);
						   	archivio = fopen(archivio_interrogazioni,"w");
						   	for(int i=0;i<n_interrogazioni;i++)
						   		if(interrogazioni[i].alunno != cod)
								   fwrite(&interrogazioni[i],sizeof(interrogazioni[0]),1,archivio);
						   	fclose(archivio);
							archivio = fopen(archivio_alunni,"w");
						   for(int i=0;i<n_aln;i++)
						   if(alunni[i].codice != cod)
						        fwrite(&alunni[i],sizeof(alunni[0]),1,archivio);
						   fclose(archivio);
						   n_aln--;
						   archivio = fopen(archivio_alunni,"r+");
						   for(int i=0;i<n_aln;i++)
						        fread(&alunni[i],sizeof(alunni[0]),1,archivio);
						   fclose(archivio);
						   stampa_lista_alunni(alunni,pag,n_aln);
						   getch();
						}
					}
				break;
			}
		}
	}while(scelta != 4);
}

void menu_interrogazioni()
{
	archivio = fopen(archivio_materie,"r+");
	for(int i=0;i<n_materie;i++)
		fread(&materie[i],sizeof(materie[0]),1,archivio);
	fclose(archivio);
	archivio = fopen(archivio_alunni,"r+");
	for(int i=0;i<n_alunni;i++)
		fread(&alunni[i],sizeof(alunni[0]),1,archivio);
	fclose(archivio);
	stampa_struttura();
	colore("NERO");
	archivio = fopen(archivio_interrogazioni,"r+");
	fseek(archivio,0,2);
	int n_int = ftell(archivio) / sizeof(interrogazioni[0]);
	int pag = 1;
	int n_pag = n_int/13;
	if(n_int%13 != 0)
		n_pag++;
	if(n_pag == 0)
		pag = 0;
	fseek(archivio,0,0);
	for(int i=0;i<n_int;i++)
	{
		fread(&interrogazioni[i],sizeof(interrogazioni[i]),1,archivio);
	}
	do{
		n_pag = n_int/13;
		if(n_int%13 != 0)
			n_pag++;
		if(pag>n_pag)
			pag = n_pag;
		stampa_lista_interrogazioni(interrogazioni,pag,n_int,materie,alunni);
		stampa_aiuto("SELEZIONA UN OPZIONE","TRA LE DISPONIBILI");
clear(26,23,54,24);
gotoxy(27,23);cout<<"FRECCIA SU/GIU - SCORRI";
gotoxy(27,24);cout<<"INVIO - SELEZIONA";
		scelta = menu_interattivo_interrogazioni();
		switch(scelta)
		{
			case -1:{
                 if(pag>1)pag--;
                 break;}          
            case -2:{
                 if(pag<n_pag)pag++;
                 break;}
			case 1:{
				colore("NERO");
				clear(24,3,56,21);
				colore("ROSSO");
				centra("AGGIUNGI INTERROGAZIONE",3);
				colore("NERO");
				gotoxy(24,5);cout<<"MATERIA";
				stampa_cornice(25,6,28,8,"");
				gotoxy(50,5);cout<<"AMBITO";
				stampa_cornice(51,6,54,8,"");
				centra("  ALUNNO",5);
				stampa_text_box(7,2);
				gotoxy(26,9);cout<<"VOTO";
				stampa_cornice(25,10,31,12,"");
				gotoxy(48,9);cout<<"DATA";
				stampa_cornice(44,10,55,12,"");
				
				
				
				int n_pag_mat = n_materie/13;
				if(n_materie%13 != 0)n_pag_mat++;
				int pag_mat = 1;
				archivio = fopen(archivio_materie,"r+");
				for(int i=0;i<n_materie;i++)
					fread(&materie[i],sizeof(materie[0]),1,archivio);
				fclose(archivio);
				stampa_lista_materie(materie,pag_mat,n_materie);
				char accett[] = "0123456789";
				int n_let = 0;
				int n = 0;
				char lettera;
				int tasto;
				bool flag;
				stampa_aiuto("INSERISCI IL CODICE","DELLA MATERIA");
clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
				do{
					flag = false;
					gotoxy(26+n_let,7);
					tasto = getch();
					lettera = tasto;
					if(trova_car(accett,lettera) != -1 && n_let < 2)
			       	 {
			       	 	cout<<lettera;
			       	 	n*=10;
			       	 	n+=lettera - '0';
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(26+n_let,7);
					 	cout<<" ";
					 	n/=10;
					 }
					 if(lettera == 73 && pag_mat>1)
					 {
					    pag_mat--;
					 	stampa_lista_materie(materie,pag_mat,n_materie);
					 }
					 if(lettera == 81 && pag_mat<n_pag_mat)
					 {
					    pag_mat++;
					 	stampa_lista_materie(materie,pag_mat,n_materie);
				     }
				     for(int i=0;i<n_materie;i++)
				     	if(materie[i].codice == n)
				     		flag = true;
				    if(tasto == 13 && !flag)
				    	stampa_errore("CODICE MATERIA","TROPPO CORTO!");
				}while(tasto != 13 || !flag);
				interrogazioni[n_int].materia = n;
				clear_errore();
				int n_pag_aln = n_alunni/13;
				if(n_alunni%13 != 0)n_pag_aln++;
				int pag_aln = 1;
				archivio = fopen(archivio_alunni,"r+");
				for(int i=0;i<n_alunni;i++)
					fread(&alunni[i],sizeof(alunni[0]),1,archivio);
				fclose(archivio);
				stampa_lista_alunni(alunni,pag_aln,n_alunni);
				n_let = 0;
				n = 0;
				stampa_aiuto("INSERISCI IL CODICE","DELL'ALUNNO");
clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
				do{
					flag = false;
					gotoxy(39+n_let,7);
					tasto = getch();
					lettera = tasto;
					if(trova_car(accett,lettera) != -1 && n_let < 2)
			       	 {
			       	 	cout<<lettera;
			       	 	n*=10;
			       	 	n+=lettera - '0';
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(39+n_let,7);
					 	cout<<" ";
					 	n/=10;
					 }
					 if(lettera == 73 && pag_aln>1)
					 {
					    pag_aln--;
					 	stampa_lista_alunni(alunni,pag_aln,n_alunni);
					 }
					 if(lettera == 81 && pag_aln<n_pag_aln)
					 {
					    pag_aln++;
					 	stampa_lista_alunni(alunni,pag_aln,n_alunni);
				     }
				     for(int i=0;i<n_alunni;i++)
				     	if(alunni[i].codice == n)
				     		flag = true;
				    if(tasto == 13 && !flag)
				    	stampa_errore("CODICE MATERIA","TROPPO CORTO!");
				}while(tasto != 13 || !flag);
				interrogazioni[n_int].alunno = n;
				clear_errore();
				clear(0,3,22,21);
				colore("ROSSO");
				stampa_distanza("HELP IN LINEA",3,4,'s');
				colore("NERO");
				gotoxy(1,5);cout<<"AMBTII PRESENTI";
				gotoxy(2,7);cout<<"01 - SCRITTO";
				gotoxy(2,8);cout<<"02 - ORALE";
				gotoxy(2,9);cout<<"03 - PRATICO";
				n_let = 0;
				n = 0;
				stampa_aiuto("INSERISCI IL CODICE","DELL'AMBITO");
clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
				do{
					flag = false;
					gotoxy(52+n_let,7);
					tasto = getch();
					lettera = tasto;
					if(trova_car(accett,lettera) != -1 && n_let < 2)
			       	 {
			       	 	cout<<lettera;
			       	 	n*=10;
			       	 	n+=lettera - '0';
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(52+n_let,7);
					 	cout<<" ";
					 	n/=10;
					 }
				     for(int i=0;i<3;i++)
				     	if(ambiti[i].codice == n)
				     		flag = true;
				    if(tasto == 13 && !flag)
				    	stampa_errore("CODICE AMBITO","TROPPO CORTO!");
				}while(tasto != 13 || !flag);
				interrogazioni[n_int].ambito = n;
				clear_errore();
				clear(0,3,22,21);
				colore("ROSSO");
				stampa_distanza("HELP IN LINEA",3,4,'s');
				colore("NERO");
				gotoxy(1,5);cout<<"RANGE VOTI";
				gotoxy(2,7);cout<<"VOTO MINIMO";
				gotoxy(3,8);cout<<classe.voto_min;
				gotoxy(2,9);cout<<"VOTO MASSIMO";
				gotoxy(3,10);cout<<classe.voto_max;
				stampa_aiuto("INSERISCI IL VOTO","DELL'INTERR.");
clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 . - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
				char accet[] = "0123456789.";
				n_let = 0;
				float v = 0;
				char voto[5];
				do{
					flag = false;
					gotoxy(26+n_let,11);
					tasto = getch();
					lettera = tasto;
					if(trova_car(accet,lettera) != -1 && n_let < 5)
			       	 {
			       	 	cout<<lettera;
			       	 	voto[n_let] = lettera;
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(26+n_let,11);
					 	cout<<" ";
					 }
					 voto[n_let] = '\0';
				    if(controllo_voto(voto));
				     	v = string_float(voto);
				    if(v>= classe.voto_min && v<=classe.voto_max)
				    	flag = true;
				    if(tasto == 13 && !flag)
				    	stampa_errore("VOTO NON VALIDO!","");
				}while(tasto != 13 || !flag);
				interrogazioni[n_int].voto = v;
	            clear_errore();
				clear(0,3,22,21);
				colore("ROSSO");
				stampa_distanza("HELP IN LINEA",3,4,'s');
				colore("NERO");
				stampa_aiuto("INSERISCI LA DATA","DELL'INTERR.");
clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 / - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
				char acce[] = "/0123456789";
				char dat[11];
				n_let = 0;
			    do{
			       	 gotoxy(45+n_let,11);
			       	 tasto = getch();
			       	 char lettera = tasto;
			       	 if(trova_car(acce,lettera) != -1 && n_let < 10)
			       	 {
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	dat[n_let] = lettera;
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(45+n_let,11);
					 	cout<<" ";
					 }
					dat[n_let] = '\0';
					if(tasto == 13 && !controllo_data(dat))
						stampa_errore("DATA NON VALIDA!","");
				   }while(tasto != 13 || !controllo_data(dat));
				   strcpy(interrogazioni[n_int].data,dat);
				   clear_errore();
				interrogazioni[n_int].codice = interrogazioni[n_int-1].codice + 1;
				centra("INTERROGAZIONE AGGIUNTA",14);
				centra("CORRETTAMENTE!",15);
				stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
				clear(26,23,54,24);
				archivio = fopen(archivio_interrogazioni,"r+");
				fseek(archivio,0,2);
				fwrite(&interrogazioni[n_int],sizeof(interrogazioni[0]),1,archivio);
				fclose(archivio);
				n_int++;
				if(pag == 0)
					pag++;
				stampa_lista_interrogazioni(interrogazioni,pag,n_int,materie,alunni);
				getch();
				break;
			}
			case 2:{
				colore("NERO");
				clear(24,3,56,21);
				colore("ROSSO");
				centra("MODIFICA INTERROGAZIONE",3);
				colore("NERO");
				centra("  CODICE",5);
				stampa_text_box(7,3);
				int codice = 0;
			    int tasto;
			    int n_let = 0;
			    char accettabili[] = "0123456789";
			    stampa_aiuto("INSERISCI IL CODICE","DELL'INTERR.");
clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
			    do{
			       	 gotoxy(39+n_let,7);
			       	 tasto = getch();
			       	 char lettera = tasto;
			       	 if(trova_car(accettabili,lettera) != -1 && n_let < 3)
			       	 {
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	codice*=10;
			       	 	codice+=lettera - '0';
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	codice/=10;
					 	gotoxy(39+n_let,7);
					 	cout<<" ";
					 }
					 if(lettera == 73 && pag>1)
					 {
					    pag--;
					 	stampa_lista_interrogazioni(interrogazioni,pag,n_int,materie,alunni);
					 }
					 if(lettera == 81 && pag<n_pag)
					{
					    pag++;
					 	stampa_lista_interrogazioni(interrogazioni,pag,n_int,materie,alunni);
					}
					if(tasto == 13 && n_let<1)
						stampa_errore("CODICE INTERROGAZIONE","NON VALIDO");
				   }while(tasto != 13 || n_let<1);
				   clear_errore();
				   bool esiste = false;
				   for(int i=0;i<n_int;i++)
				   		if(interrogazioni[i].codice == codice)
				   			esiste = true;
				   int cod = codice;
				   codice = 0;
				   while(interrogazioni[codice].codice != cod)
				   {codice++;}
				   if(!esiste)
				   {
				   	centra("INTERROGAZIONE",10);
				   	centra("NON TROVATA!",11);
				   	clear(26,23,54,24);
				   	stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
				   	getch();
				   }
				   else
				   {
				   	colore("NERO");
					clear(24,3,56,21);
					colore("ROSSO");
					centra("MODIFICA INTERROGAZIONE",3);
					colore("NERO");
				   	int pos = codice;
				   	gotoxy(24,5);cout<<"MATERIA";
					stampa_cornice(25,6,28,8,"");
					gotoxy(50,5);cout<<"AMBITO";
					stampa_cornice(51,6,54,8,"");
					centra("  ALUNNO",5);
					stampa_text_box(7,2);
					gotoxy(26,9);cout<<"VOTO";
					stampa_cornice(25,10,31,12,"");
					gotoxy(48,9);cout<<"DATA";
					stampa_cornice(44,10,55,12,"");
					gotoxy(26,7);printf("%02d",interrogazioni[pos].materia);
					gotoxy(39,7);printf("%02d",interrogazioni[pos].alunno);
					gotoxy(52,7);printf("%02d",interrogazioni[pos].ambito);
					gotoxy(26,11);cout<<interrogazioni[pos].voto;
					gotoxy(45,11);cout<<interrogazioni[pos].data;
					stampa_aiuto("SELEZIONA UN OPZIONE","TRA LE DISPONIBILI");
					clear(26,23,54,24);
					gotoxy(27,23);cout<<"FRECCIA SU/GIU - SCORRI";
					gotoxy(27,24);cout<<"INVIO - SELEZIONA";
					centra("MODIFICARE L'INTERROGAZIONE?",14);
					centra("NO",16);
					colore("GIALLO");
					centra("SI",15);
						int tasto;
						int scelta = 1;
						do{
							colore("NERO");
							gotoxy(0,0);
							tasto = getch();
							switch(tasto)
								{
								case 72:scelta = 1;
								   	 	colore("GIALLO");
								   	 	centra("SI",15);
								   	 	colore("NERO");
								   	 	centra("NO",16);break;
								case 80:scelta = 2;
								   	 	colore("GIALLO");
								   	 	centra("NO",16);
								   	 	colore("NERO");
								   	 	centra("SI",15);break;
							}
						}while(tasto != 13);
				int posiz = pos;
				if(scelta == 1)
				{
				colore("NERO");
				clear(24,3,56,21);
				colore("ROSSO");
				centra("MODIFICA INTERROGAZIONE",3);
				colore("NERO");
				gotoxy(24,5);cout<<"MATERIA";
				stampa_cornice(25,6,28,8,"");
				gotoxy(50,5);cout<<"AMBITO";
				stampa_cornice(51,6,54,8,"");
				centra("  ALUNNO",5);
				stampa_text_box(7,2);
				gotoxy(26,9);cout<<"VOTO";
				stampa_cornice(25,10,31,12,"");
				gotoxy(48,9);cout<<"DATA";
				stampa_cornice(44,10,55,12,"");
				int n_pag_mat = n_materie/13;
				if(n_materie%13 != 0)n_pag_mat++;
				int pag_mat = 1;
				archivio = fopen(archivio_materie,"r+");
				for(int i=0;i<n_materie;i++)
					fread(&materie[i],sizeof(materie[0]),1,archivio);
				fclose(archivio);
				stampa_lista_materie(materie,pag_mat,n_materie);
				char accett[] = "0123456789";
				int n_let = 0;
				int n = 0;
				char lettera;
				int tasto;
				bool flag;
				stampa_aiuto("INSERISCI IL CODICE","DELLA MATERIA");
clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
				do{
					flag = false;
					gotoxy(26+n_let,7);
					tasto = getch();
					lettera = tasto;
					if(trova_car(accett,lettera) != -1 && n_let < 2)
			       	 {
			       	 	cout<<lettera;
			       	 	n*=10;
			       	 	n+=lettera - '0';
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(26+n_let,7);
					 	cout<<" ";
					 	n/=10;
					 }
					 if(lettera == 73 && pag_mat>1)
					 {
					    pag_mat--;
					 	stampa_lista_materie(materie,pag_mat,n_materie);
					 }
					 if(lettera == 81 && pag_mat<n_pag_mat)
					 {
					    pag_mat++;
					 	stampa_lista_materie(materie,pag_mat,n_materie);
				     }
				     for(int i=0;i<n_materie;i++)
				     	if(materie[i].codice == n)
				     		flag = true;
				    if(tasto == 13 && !flag)
				    	stampa_errore("CODICE MATERIA","TROPPO CORTO!");
				}while(tasto != 13 || !flag);
				interrogazioni[posiz].materia = n;
				clear_errore();
				int n_pag_aln = n_alunni/13;
				if(n_alunni%13 != 0)n_pag_aln++;
				int pag_aln = 1;
				archivio = fopen(archivio_alunni,"r+");
				for(int i=0;i<n_alunni;i++)
					fread(&alunni[i],sizeof(alunni[0]),1,archivio);
				fclose(archivio);
				stampa_lista_alunni(alunni,pag_aln,n_alunni);
				n_let = 0;
				n = 0;
				stampa_aiuto("INSERISCI IL CODICE","DELL'ALUNNO");
clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
				do{
					flag = false;
					gotoxy(39+n_let,7);
					tasto = getch();
					lettera = tasto;
					if(trova_car(accett,lettera) != -1 && n_let < 2)
			       	 {
			       	 	cout<<lettera;
			       	 	n*=10;
			       	 	n+=lettera - '0';
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(39+n_let,7);
					 	cout<<" ";
					 	n/=10;
					 }
					 if(lettera == 73 && pag_aln>1)
					 {
					    pag_aln--;
					 	stampa_lista_alunni(alunni,pag_aln,n_alunni);
					 }
					 if(lettera == 81 && pag_aln<n_pag_aln)
					 {
					    pag_aln++;
					 	stampa_lista_alunni(alunni,pag_aln,n_alunni);
				     }
				     for(int i=0;i<n_alunni;i++)
				     	if(alunni[i].codice == n)
				     		flag = true;
				    if(tasto == 13 && !flag)
				    	stampa_errore("CODICE MATERIA","TROPPO CORTO!");
				}while(tasto != 13 || !flag);
				interrogazioni[posiz].alunno = n;
				clear_errore();
				clear(0,3,22,21);
				colore("ROSSO");
				stampa_distanza("HELP IN LINEA",3,4,'s');
				colore("NERO");
				gotoxy(1,5);cout<<"AMBTII PRESENTI";
				gotoxy(2,7);cout<<"01 - SCRITTO";
				gotoxy(2,8);cout<<"02 - ORALE";
				gotoxy(2,9);cout<<"03 - PRATICO";
				n_let = 0;
				n = 0;
				stampa_aiuto("INSERISCI IL CODICE","DELL'AMBITO");
clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
				do{
					flag = false;
					gotoxy(52+n_let,7);
					tasto = getch();
					lettera = tasto;
					if(trova_car(accett,lettera) != -1 && n_let < 2)
			       	 {
			       	 	cout<<lettera;
			       	 	n*=10;
			       	 	n+=lettera - '0';
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(52+n_let,7);
					 	cout<<" ";
					 	n/=10;
					 }
				     for(int i=0;i<3;i++)
				     	if(ambiti[i].codice == n)
				     		flag = true;
				    if(tasto == 13 && !flag)
				    	stampa_errore("CODICE AMBITO","TROPPO CORTO!");
				}while(tasto != 13 || !flag);
				interrogazioni[posiz].ambito = n;
				clear_errore();
				clear(0,3,22,21);
				colore("ROSSO");
				stampa_distanza("HELP IN LINEA",3,4,'s');
				colore("NERO");
				gotoxy(1,5);cout<<"RANGE VOTI";
				gotoxy(2,7);cout<<"VOTO MINIMO";
				gotoxy(3,8);cout<<classe.voto_min;
				gotoxy(2,9);cout<<"VOTO MASSIMO";
				gotoxy(3,10);cout<<classe.voto_max;
				char accet[] = "0123456789.";
				n_let = 0;
				float v = 0;
				char voto[5];
				stampa_aiuto("INSERISCI IL VOTO","DELL'INTERR.");
clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 . - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
				do{
					flag = false;
					gotoxy(26+n_let,11);
					tasto = getch();
					lettera = tasto;
					if(trova_car(accet,lettera) != -1 && n_let < 5)
			       	 {
			       	 	cout<<lettera;
			       	 	voto[n_let] = lettera;
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(26+n_let,11);
					 	cout<<" ";
					 }
					 voto[n_let] = '\0';
				    if(controllo_voto(voto));
				     	v = string_float(voto);
				    if(v>= classe.voto_min && v<=classe.voto_max)
				    	flag = true;
				    if(tasto == 13 && !flag)
				    	stampa_errore("VOTO NON VALIDO!","");
				}while(tasto != 13 || !flag);
				interrogazioni[posiz].voto = v;
				clear_errore();
				clear(0,3,22,21);
				colore("ROSSO");
				stampa_distanza("HELP IN LINEA",3,4,'s');
				colore("NERO");
				stampa_aiuto("INSERISCI LA DATA","DELL'INTERR.");
clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 / - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
				char acce[] = "/0123456789";
				char dat[11];
				n_let = 0;
			    do{
			       	 gotoxy(45+n_let,11);
			       	 tasto = getch();
			       	 char lettera = tasto;
			       	 if(trova_car(acce,lettera) != -1 && n_let < 10)
			       	 {
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	dat[n_let] = lettera;
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	gotoxy(45+n_let,11);
					 	cout<<" ";
					 }
					dat[n_let] = '\0';
					if(tasto == 13 && !controllo_data(dat))
						stampa_errore("DATA NON VALIDA!","");
				   }while(tasto != 13 || !controllo_data(dat));
				   clear_errore();
				   strcpy(interrogazioni[posiz].data,dat);
				centra("INTERROGAZIONE MODIFICATA",14);
				centra("CORRETTAMENTE!",15);
				archivio = fopen(archivio_interrogazioni,"w");
				for(int i=0;i<n_int;i++)
					fwrite(&interrogazioni[i],sizeof(interrogazioni[0]),1,archivio);
				fclose(archivio);
				stampa_lista_interrogazioni(interrogazioni,pag,n_int,materie,alunni);
				stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
				clear(26,23,54,24);
				getch();
			}
				}
				break;
			}
			case 3:{
				colore("NERO");
				clear(24,3,56,21);
				colore("ROSSO");
				centra("ELIMINA INTERROGAZIONE",3);
				colore("NERO");
				centra("  CODICE",5);
				stampa_text_box(7,3);
				int codice = 0;
			    int tasto;
			    int n_let = 0;
			    char accettabili[] = "0123456789";
			    stampa_aiuto("INSERISCI IL CODICE","DELL'INTERR.");
clear(26,23,54,24);
gotoxy(27,23);cout<<"0-9 - SCRIVI";
gotoxy(27,24);cout<<"INVIO - CONFERMA";
			    do{
			       	 gotoxy(39+n_let,7);
			       	 tasto = getch();
			       	 char lettera = tasto;
			       	 if(trova_car(accettabili,lettera) != -1 && n_let < 3)
			       	 {
			       	 	converti_car(lettera);
			       	 	cout<<lettera;
			       	 	codice*=10;
			       	 	codice+=lettera - '0';
			       	 	n_let++;
					 }
					 if(lettera == 8 && n_let>0)
					 {
					 	n_let--;
					 	codice/=10;
					 	gotoxy(39+n_let,7);
					 	cout<<" ";
					 }
					 if(lettera == 73 && pag>1)
					 {
					    pag--;
					 	stampa_lista_interrogazioni(interrogazioni,pag,n_int,materie,alunni);
					 }
					 if(lettera == 81 && pag<n_pag)
					{
					    pag++;
					 	stampa_lista_interrogazioni(interrogazioni,pag,n_int,materie,alunni);
					}
					if(tasto == 13 && n_let<1)
						stampa_errore("CODICE INTERROGAZIONE","TROPPO CORTO!");
				   }while(tasto != 13 || n_let<1);
				   clear_errore();
				   bool esiste = false;
				   for(int i=0;i<n_int;i++)
				   		if(interrogazioni[i].codice == codice)
				   			esiste = true;
				   int cod = codice;
				   codice = 0;
				   while(interrogazioni[codice].codice != cod)
				   {codice++;}
				   if(!esiste)
				   {
				   	centra("INTERROGAZIONE",10);
				   	centra("NON TROVATA!",11);
				   	stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
				   	clear(26,23,54,24);
				   	getch();
				   }
				   else
				   {
				   	colore("NERO");
					clear(24,3,56,21);
					colore("ROSSO");
					centra("ELIMINA INTERROGAZIONE",3);
					colore("NERO");
				   	int pos = codice;
				   	gotoxy(24,5);cout<<"MATERIA";
					stampa_cornice(25,6,28,8,"");
					gotoxy(50,5);cout<<"AMBITO";
					stampa_cornice(51,6,54,8,"");
					centra("  ALUNNO",5);
					stampa_text_box(7,2);
					gotoxy(26,9);cout<<"VOTO";
					stampa_cornice(25,10,31,12,"");
					gotoxy(48,9);cout<<"DATA";
					stampa_cornice(44,10,55,12,"");
					gotoxy(26,7);printf("%02d",interrogazioni[pos].materia);
					gotoxy(39,7);printf("%02d",interrogazioni[pos].alunno);
					gotoxy(52,7);printf("%02d",interrogazioni[pos].ambito);
					gotoxy(26,11);cout<<interrogazioni[pos].voto;
					gotoxy(45,11);cout<<interrogazioni[pos].data;
					stampa_aiuto("SELEZIONA UN OPZIONE","TRA LE DISPONIBILI");
clear(26,23,54,24);
gotoxy(27,23);cout<<"FRECCIA SU/GIU - SCORRI";
gotoxy(27,24);cout<<"INVIO - SELEZIONA";
					centra("ELIMINARE L'INTERROGAZIONE?",14);
					centra("NO",16);
					colore("GIALLO");
					centra("SI",15);
						int tasto;
						int scelta = 1;
						do{
							colore("NERO");
							gotoxy(0,0);
							tasto = getch();
							switch(tasto)
								{
								case 72:scelta = 1;
								   	 	colore("GIALLO");
								   	 	centra("SI",15);
								   	 	colore("NERO");
								   	 	centra("NO",16);break;
								case 80:scelta = 2;
								   	 	colore("GIALLO");
								   	 	centra("NO",16);
								   	 	colore("NERO");
								   	 	centra("SI",15);break;
							}
						}while(tasto != 13);
				int posiz = pos;
				if(scelta == 1)
				{
					stampa_aiuto("PREMI UN TASTO","PER CONTINUARE");
				   	clear(26,23,54,24);
					centra("INTERROGAZIONE ELIMINATA",18);
					centra("CORRETTAMENTE",19);
					archivio = fopen(archivio_interrogazioni,"w");
						for(int i=0;i<n_int;i++)
						   		if(i!=posiz)
								   fwrite(&interrogazioni[i],sizeof(interrogazioni[0]),1,archivio);
					fclose(archivio);
					n_int--;
					archivio = fopen(archivio_interrogazioni,"r+");
					for(int i=0;i<n_int;i++)
						   	fread(&interrogazioni[i],sizeof(interrogazioni[0]),1,archivio);
					fclose(archivio);
					stampa_lista_interrogazioni(interrogazioni,pag,n_int,materie,alunni);
					getch();
				}
				break;
		    }
          }
	    }
	}while(scelta != 4);
}

void risultati()
{
	stampa_aiuto("VISUALIZZA I","RISULTATI");
	clear(26,23,54,24);
gotoxy(27,23);cout<<"FRECC. SU/GIU/SX/DX - SCORRI";
gotoxy(27,24);cout<<"INVIO - ESCI";
	archivio = fopen(archivio_materie,"r+");
	for(int i=0;i<n_materie;i++)
		fread(&materie[i],sizeof(materie[0]),1,archivio);
	fclose(archivio);
	archivio = fopen(archivio_alunni,"r+");
	for(int i=0;i<n_alunni;i++)
		fread(&alunni[i],sizeof(alunni[0]),1,archivio);
	fclose(archivio);
	archivio = fopen(archivio_interrogazioni,"r+");
	for(int i=0;i<n_interrogazioni;i++)
	{
		fseek(archivio,i*sizeof(interrogazioni[0]),0);
		fread(&interrogazioni[i],sizeof(interrogazioni[0]),1,archivio);
	}
	fclose(archivio);
	int tasto;
	int npagx = n_materie/5;
	if(n_materie%5 != 0)
		npagx++;
	int npagy = n_alunni/7;
	if(n_alunni%7 != 0)
		npagy++;
	int pagx = 1,pagy = 1;
	stampa_tabella_risultati();
	riempi_tabella(pagx,pagy);
	do{
		tasto = getch();
		if(tasto == 72)
		{
			if(pagy>1)
			{
				pagy--;
				stampa_tabella_risultati();
				riempi_tabella(pagx,pagy);
			}
		}
		if(tasto == 80)
		{
			if(pagy<npagy)
			{
				pagy++;
				stampa_tabella_risultati();
				riempi_tabella(pagx,pagy);
			}
		}
		if(tasto == 75)
		{
			if(pagx>1)
			{
				pagx--;
				stampa_tabella_risultati();
				riempi_tabella(pagx,pagy);
			}
		}
		if(tasto == 77)
		{
			if(pagx<npagx)
			{
				pagx++;
				stampa_tabella_risultati();
				riempi_tabella(pagx,pagy);
			}
		}
	}while(tasto != 13);
}

void riempi_tabella(int pagx,int pagy)
{
	int materia1 = 5*pagx - 5;
	for(int i=materia1;i<5+materia1 && i<n_materie;i++)
	{
		scrivi(materie[i].nome,23+((i-materia1)*9),4,23+((i-materia1)*9)+8);
		gotoxy(23+((i-materia1)*9),6);cout<<"SC";
		gotoxy(26+((i-materia1)*9),6);cout<<"OR";
		gotoxy(29+((i-materia1)*9),6);cout<<"PR";
	}
	int alunno1 = 7*pagy - 7;
	for(int i=alunno1;i<7+alunno1 && i<n_alunni;i++)
	{
		int y = 8+((i-alunno1)*2);
		gotoxy(1,y);printf("%02d",alunni[i].codice);
		scrivi(alunni[i].nominativo,4,y,21);
		int numero_insuff = 0;
		int codice_alunno = alunni[i].codice;
		float media = 0;
		int numero_int = 0;
		for(int j=0;j<n_interrogazioni;j++)
		{
			if(interrogazioni[j].alunno == codice_alunno)
			{
				media+=interrogazioni[j].voto;
				numero_int++;
				if(interrogazioni[j].voto<classe.voto_suff)
					numero_insuff++;
			}
		}
		media/=numero_int;
		float p = media - int(media);
		p*=100;
		gotoxy(68,y);
		if(numero_int > 0)
			printf("%2d.%02d",int(media),int(p));
		else
			cout<<"  -";
		for(int k=materia1;k<5+materia1 && k<n_materie;k++)
		{
			int x = 23+((k-materia1)*9);
			int codice_mat = materie[k].codice;
			float media1 = 0;
			float media2 = 0;
			float media3 = 0;
			int n1 = 0;
			int n2 = 0;
			int n3 = 0;
			for(int j=0;j<n_interrogazioni;j++)
			{
				if(interrogazioni[j].alunno == codice_alunno)
					if(interrogazioni[j].materia == codice_mat)
					{
						if(interrogazioni[j].ambito == 1)
						{
							n1++;
							media1+=interrogazioni[j].voto;
						}
						if(interrogazioni[j].ambito == 2)
						{
							n2++;
							media2+=interrogazioni[j].voto;
						}
						if(interrogazioni[j].ambito == 3)
						{
							n2++;
							media2+=interrogazioni[j].voto;
						}
					}
			}
			if(n1>0)
				media1/=n1;
			if(n2>0)
				media2/=n2;
			if(n3>0)
				media3/=n3;
			char v[2];
			if(media1+0.10>=classe.voto_suff)
				colore("SFONDOVERDE");
			else
				colore("SFONDOROSSO");
			voto_string(media1,v);
			gotoxy(x,y);
			cout<<v;
			if(media2+0.10>=classe.voto_suff)
				colore("SFONDOVERDE");
			else
				colore("SFONDOROSSO");
			voto_string(media2,v);
			gotoxy(x+3,y);
			cout<<v;
			if(media3+0.10>=classe.voto_suff)
				colore("SFONDOVERDE");
			else
				colore("SFONDOROSSO");
			voto_string(media3,v);
			gotoxy(x+6,y);
			cout<<v;
			colore("NERO");
			if(media1 == 0)
			{
				gotoxy(x,y);
				cout<<"--";
			}
			if(media2 == 0)
			{
				gotoxy(x+3,y);
				cout<<"--";
			}
			if(media3 == 0)
			{
				gotoxy(x+6,y);
				cout<<"--";
			}
		}
		gotoxy(74,y);
		if(numero_insuff == 0)
			cout<<"PROM.";
		if(numero_insuff > 0 && numero_insuff < 3)
			cout<<"DEBI.";
		if(numero_insuff > 2)
			cout<<"BOCC.";
		if(numero_int == 0)
		{
			gotoxy(74,y);cout<<"  -  ";
		}
		
	}
}



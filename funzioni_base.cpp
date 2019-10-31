#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdio.h>
#include <io.h>
using namespace std;

void gotoxy(short x, short y);
void setcolor(short color);
void colore(char c[]);
void scrivi(char stringa[],int x,int y, int x2);

void centra(char stringa[],int riga);
void stampa_distanza(char stringa[],int riga,int distanza,char lato);

void clear(int colAS,int rigAS,int colAD,int rigAD);
void clear();

void appunta(char stringa[],int max);
void concatena(char stringa1[],char stringa2[]);
void sotto_stringa(char stringa[],int inizio,int lunghezza,char subStringa[]);

void converti_str(char stringa[]);
void converti_car(char &car);
int string_int(char stringa[]);

int trova_car(char nominativo[],char car);
void estrai_nominativo(char nominativo[],char cognome[],char nome[]);

bool controllo_data(char data[]);
void copia_str(char s1[],char s2[]);
bool controllo_nominativo(char nominativo[]);
int conta_cifre(int n);
void int_string(int n,char str[]);

void crea_nomi_archivi(char archivio[],char materie[],char alunni[],char classe[],char interrogazioni[],char ambiti[]);

bool controllo_voto(char voto[5])
{
	int conta = 0;
	for(int i=0;i<strlen(voto);i++)
		if(voto[i] == '.')
			conta++;
	if(conta>1)
		return false;
	if(voto[0] == '.')
		return false;
	if(voto[strlen(voto)-1] == '.')
		return false;
	return true;
}

float string_float(char voto[])
{
	float v = 0;
	int pos = trova_car(voto,'.');
	if(pos == -1)
		pos = strlen(voto);
	for(int i=0;i<pos;i++)
	{
		v*=10;
		v+=voto[i]-'0';
	}
	for(int i=pos+1;i<strlen(voto) && i<pos+3;i++)
	{
		float cifra = voto[i]-'0';
		for(int j=0;j<i-pos;j++)
			cifra/=10;
		v+=cifra;
	}
	return v;
}

void colore(char c[])
{
	if(strcmp(c,"ROSSO") == 0)
		setcolor(12|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY);
	if(strcmp(c,"NERO") == 0)
		setcolor(0|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY);
	if(strcmp(c,"GRIGIO") == 0)
		setcolor(8|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY);
	if(strcmp(c,"GIALLO") == 0)
		setcolor(15);
	if(strcmp(c,"SFONDOVERDE") == 0)
		setcolor(0|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
	if(strcmp(c,"SFONDOROSSO") == 0)
		setcolor(0|BACKGROUND_RED|BACKGROUND_INTENSITY);
}

void scrivi(char stringa[],int x,int y, int x2)
{
	char str[20];
	strcpy(str,stringa);
	appunta(str,x2-x);
	gotoxy(x,y);
	cout<<str;
}

void int_string(int n,char str[])
{
	int cifre = conta_cifre(n);
	str[cifre] = '\0';
	for(int i=cifre-1;i>=0;i--)
	{
		str[i] = n%10 + '0';
		n/=10;
	}
}

int conta_cifre(int n)
{
	int cifre = 0;
	do{
		n/=10;
		cifre++;
	}while(n>0);
	return cifre;	
}

void copia_str(char s1[],char s2[])
{
	for(int i=0;i<strlen(s2);i++)
		s1[i] = s2[i];
	s1[strlen(s2)] = '\0';
}

void gotoxy(short x, short y)
{
  COORD pos = {x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setcolor(short color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,color);
}

void centra(char stringa[],int riga)
{
	int l = strlen(stringa);
	gotoxy(39 - l/2,riga);
	cout<<stringa;
}

void stampa_distanza(char stringa[],int riga,int distanza,char lato)
{
	int l = strlen(stringa);
	if(lato == 's')
	   gotoxy(distanza,riga);
	if(lato == 'd')
	   gotoxy(79-(distanza+l-1),riga);
	cout<<stringa;
}

void clear(int colAS,int rigAS,int colAD,int rigAD)
{
	for(int i=colAS;i<=colAD;i++)
	{
		for(int j=rigAS;j<=rigAD;j++)
		{
			gotoxy(i,j);
			cout<<" ";
		}
	}
}

void clear()
{
	for(int i=0;i<=79;i++)
	{
		for(int j=3;j<=21;j++)
		{
			gotoxy(i,j);
			cout<<" ";
		}
	}
}

void appunta(char stringa[],int max)
{
	if(strlen(stringa) <= max)
	   return;
	stringa[max-1] = '.';
	stringa[max] = '\0';
}

void concatena(char stringa1[],char stringa2[])
{
	int l=strlen(stringa1);
	for(int i=0;i<strlen(stringa2);i++)
		stringa1[i+l] = stringa2[i];
	stringa1[strlen(stringa2)+l] = '\0';
}

void sotto_stringa(char stringa[],int inizio,int lunghezza,char subStringa[])
{
	for(int i=0;i<lunghezza;i++)
		subStringa[i] = stringa[i+inizio];
	subStringa[lunghezza] = '\0';
}

void converti_str(char stringa[])
{
     for(int i=0;i<strlen(stringa);i++)
         if(stringa[i]>='a' && stringa[i]<='z')
             stringa[i]-=32;
     return;
}

void converti_car(char &car)
{
	if(car>='a' && car<='z')
	   car+='A'-'a';
}

int string_int(char stringa[])
{
	int numero = 0;
	for(int i=0;i<strlen(stringa);i++)
	{
		numero *= 10;
		numero += stringa[i] - '0';
	}
	return numero;
}

int trova_car(char nominativo[],char car)
{
    for(int i=0;i<strlen(nominativo);i++)
        if(nominativo[i] == car)
            return i;
    return -1;
}

void estrai_nominativo(char nominativo[],char cognome[],char nome[])
{
	int pos = trova_car(nominativo,'/');
	sotto_stringa(nominativo,0,pos,cognome);
	sotto_stringa(nominativo,pos+1,strlen(nominativo)-pos-1,nome);
}

bool controllo_data(char data[])
{
	int giorniMese[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	if(strlen(data) != 10)
	   return false;
	if(data[2] != '/' || data[5] != '/')
	   return false;
	char sub[4];
	sotto_stringa(data,6,4,sub);
	int anno = string_int(sub);
	sotto_stringa(data,3,2,sub);
	int mese = string_int(sub);
	sotto_stringa(data,0,2,sub);
	int giorno = string_int(sub);
	if(anno % 4 == 0)
	   giorniMese[2]++;
	if(mese < 0 || mese > 12)
	   return false;
	if(giorno < 0 || giorno > giorniMese[mese])
	   return false;
	return true;
}

bool controllo_nominativo(char nominativo[])
{
	int pos;
	int conta = 0;
    for(int i=0;i<strlen(nominativo);i++)
        if(nominativo[i] == '/')
            conta++;
    if(conta != 1)
       return false;
    for(int i=0;i<strlen(nominativo);i++)
        if(nominativo[i] == '/')
            pos = i;
    if(pos<2)
       return false;
    if(strlen(nominativo) - pos < 4)
       return false;
    return true;
}

void voto_string(float media1,char v[])
{
	float l = media1 - int(media1);
	l*=100;
	if(l<10)
	{ 
				v[0] = ' ';
				v[1] = int(media1) + '0';
				if((int)media1 == 10)
				{
					v[0] = '1';
					v[1] = '0';
				}
			}
			if(l>=90)
			{
				media1++;
				v[0] = ' ';
				v[1] = int(media1) + '0';
				if(int(media1) >= 10)
				{
					v[0] = '1';
					v[1] = '0';
				}
			}
			if(l>=10 && l<40)
			{
				v[0] = int(media1) + '0';
				v[1] = '+';
			}
			if(l>=66 && l<90)
			{
				media1++;
				v[0] = int(media1) + '0';
				v[1] = '-';
				if(int(media1) >= 10)
				{
					v[0] = '1';
					v[1] = '0';
				}
			}
			if(l>=40 && l<=65)
			{
				v[0] = int(media1) + '0';
				v[1] = (char)171;
			}
}

void crea_nomi_archivi(char archivio[],char materie[],char alunni[],char classe[],char interrogazioni[],char ambiti[])
{
	strcpy(materie,"archivi/");
	strcpy(alunni,"archivi/");
	strcpy(classe,"archivi/");
	strcpy(interrogazioni,"archivi/");
	strcpy(ambiti,"archivi/");
	concatena(materie,archivio);
	concatena(alunni,archivio);
	concatena(classe,archivio);
	concatena(interrogazioni,archivio);
	concatena(ambiti,archivio);
	concatena(materie,"/");
	concatena(alunni,"/");
	concatena(classe,"/");
	concatena(interrogazioni,"/");
	concatena(ambiti,"/");
	concatena(materie,archivio);
	concatena(alunni,archivio);
	concatena(classe,archivio);
	concatena(interrogazioni,archivio);
	concatena(ambiti,archivio);
	concatena(materie,".mtr");
	concatena(alunni,".aln");
	concatena(classe,".cls");
	concatena(interrogazioni,".itr");
	concatena(ambiti,".amb");
}

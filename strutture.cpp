#include <iostream>
#include <cstdlib>
using namespace std;

struct struttura_classe
{
	char nome_scuola[20];
	char nome_classe[20];
	int voto_min;
	int voto_max;
	int voto_suff;
};

struct struttura_materia
{
	int codice;
	char nome[20];
};

struct struttura_alunno
{
	int codice;
	char nominativo[20];
	char data_nascita[11];
	char sesso;
};

struct struttura_ambito
{
	int codice;
	char nome[30];
};

struct struttura_interrogazione
{
	int codice;
	int alunno;
	int materia;
	int ambito;
	char data[11];
	float voto;
};

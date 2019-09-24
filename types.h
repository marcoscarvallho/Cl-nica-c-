#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_WARNINGS
 
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<stdio.h>
#include <stdlib.h>
#include<Windows.h>
#include<time.h>
 
#ifndef T
#define T 100
#endif
 
#ifndef t
#define t 16
#endif
 
#ifndef CP
#define CP 12
#endif
 
#ifndef CR
#define CR 9
#endif
 
#ifndef True
#define True 1
#endif
 
#ifndef False
#define False 0
#endif
 
#ifndef ESTRUTURAS
#define ESTRUTURAS
 
typedef struct paciente {
    char cpf[CP], nome[T], tel[t], email[T];
    int status;
}Tpaciente;
#endif
 
#ifndef ARVORE
#define ARVORE
 
typedef struct no {
    int pos;
    char cod[CP];
    struct no *dir, *esq;
}Tno;
#endif
 
#ifndef ESTRUTMED
#define ESTRUTMED
 
typedef struct medico{
    char crm[CR], nome[T], tel[t], email[T];
    int status, especialidade, horario[5][2];
}Tmedicos;
#endif
 
#ifndef DATA
#define DATA
 
typedef struct data{
    int dia, mes, ano;
}Tdata;
#endif
 
#ifndef ESTRUTCONS
#define ESTRUTCONS
 
typedef struct consultas{
    char crm[9], turno, cpf[12];
    int status;
    Tdata data;
}Tconsultas;
#endif
 
#ifndef FILA
#define FILA
 
typedef struct queue {
    char cpf[CP], crm[CR], turno;
    struct queue *prox;
    Tdata data;
}Tqueue;
#endif
#include"types.h"
 
void Pacientes(char crm[], Tdata data, int turno, FILE *arqC, Tno *raiz, FILE *arqP);
void marcar(char cpf[], char crm[], Tdata data, char turno, FILE *arq);
void Consultas (char cpf[], FILE *arqC, FILE *arqM, Tno *raiz);
int desmarcar(char cpf[], char crm[], Tdata data, char turno, FILE *arq);
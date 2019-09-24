#include "types.h"
#include "tree.h"
#include "validacao.h"
 
void exibirPaciente(Tno *raiz, char n[], FILE *arq);
void alterarPaciente(Tno **raiz, char n[], FILE *arq);
void cadastrarPaciente(Tno **raiz, char n[], FILE *arq);
void removerPaciente(Tno **raiz, char n[], FILE *arq);
void manutencaoC(FILE *arq, char nome[]);
int buscarNome(FILE * arq, char nomeAux[], int aux);
FILE * criarArquivo(char nome[]);
void manutencaoC(FILE *arq, char nome[]);
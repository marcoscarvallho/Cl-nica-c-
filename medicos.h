#include "types.h"
#include "tree.h"
#include "validacao.h"
#include "clientes.h"
void exibirMedico(Tno *raiz, char n[], FILE *arq);
void alterarMedico(Tno **raiz, char n[], FILE *arq);
void cadastrarMedico(Tno **raiz, char n[], FILE *arq);
void removerMedico(Tno **raiz, char n[], FILE *arq);
void manutencaoM(FILE *arq, char nome[]);
int buscarNomeM(FILE * arq, char nomeAux[], int aux);
void menuEspecialidades();
void buscaEspecialidade(FILE *arq, int especialidade);
void exibirMatriz(int matriz[5][2]);
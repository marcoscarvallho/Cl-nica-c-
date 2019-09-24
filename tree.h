#include"types.h"
 
int buscar(char n[], Tno *raiz);
void insert(Tno **raiz, char cod[], int p);
Tno *maior(Tno **raiz);
void remover_no(Tno **raiz);
void remover(Tno **raiz, char cod[]);
void setArvoreC(Tno **raiz, FILE *arq);
void deletar(Tno ** raiz);
void setArvoreM(Tno **raiz, FILE *arq);
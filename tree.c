#include"types.h"
#include "tree.h"
int buscar(char n[], Tno *raiz) {
    if (raiz == NULL)
        return -1;
    else {
        if (strcmp(n, raiz->cod) == 0)
            return raiz->pos;
        else if (strcmp(n, raiz->cod) > 0)
            return buscar(n, raiz->dir);
        else
            return buscar(n, raiz->esq);
    }
}
 
void insert(Tno **raiz, char cod[], int p) {
    if (*raiz == NULL) {
        *raiz = (Tno*)malloc(sizeof(Tno));
        strcpy((*raiz)->cod, cod);
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
        (*raiz)->pos = p;
    }
    else if (strcmp(cod, (*raiz)->cod) < 0)
        insert(&((*raiz)->esq), cod, p);
    else
        insert(&((*raiz)->dir), cod, p);
}
 
void remover_no(Tno **raiz) {
    Tno *pos;
    pos = *raiz;
    if ((*raiz)->esq == NULL && (*raiz)->dir == NULL)
        *raiz = NULL;
    else if ((*raiz)->esq == NULL)
        *raiz = (*raiz)->dir;
    else if ((*raiz)->dir == NULL)
        *raiz = (*raiz)->esq;
    else {
        pos = maior(&((*raiz)->esq));
        strcpy((*raiz)->cod, pos->cod);
        (*raiz)->pos = pos->pos;
    }
    free(pos);
}
 
void remover(Tno **raiz, char cod[]) {
    int result;
    if (*raiz == NULL)
        printf("Elemento não encontrado.\n");
    else {
        result = strcmp(cod, (*raiz)->cod);
        if (result == 0)
            remover_no(raiz);
        else if (result < 0)
            remover((&(*raiz)->esq), cod);
        else
            remover((&(*raiz)->dir), cod);
    }
}
 
 
 
Tno *maior(Tno **raiz) {
    Tno *aux;
    aux = *raiz;
    if (aux->dir == NULL) {
        *raiz = (*raiz)->esq;
        return (aux);
    }
    else
        return maior(&((*raiz)->dir));
}
 
void setArvoreC(Tno **raiz, FILE *arq) {
    Tpaciente aux;
    int pos, resp;
    fseek(arq, 0, 0);
    while (1) {
        pos = fread(&aux, sizeof(Tpaciente), 1, arq);
        if (pos != 1) {
            if (!feof(arq))
                printf("Erro na leitura.\n");
            break;
        }
        else {
            resp = ftell(arq) / sizeof(Tpaciente) - 1;
            insert(&(*raiz), aux.cpf, resp);
        }
    }
}
 
void deletar(Tno ** raiz) {
    if (*raiz != NULL) {
        deletar(&((*raiz)->esq));
        deletar(&((*raiz)->dir));
        free(*raiz);
    }
}
 
void setArvoreM(Tno **raiz, FILE *arq) {
    Tmedicos aux;
    int status, resp;
    fseek(arq, 0, 0);
    while (1) {
        status = fread(&aux, sizeof(Tmedicos), 1, arq);
        if (status != 1) {
            if (!feof(arq))
                printf("Erro de leitura.\n");
            break;
        }
        else {
            resp = ftell(arq) / sizeof(Tmedicos) - 1;
            insert(&(*raiz), aux.crm, resp);
        }
    }
}
#include"types.h"
#include"clientes.h"
#include"tree.h"
#include"validacao.h"
 
FILE * criarArquivo(char nome[]) {
    FILE * arq;
    arq = fopen(nome, "r+b");
    if (arq == NULL) {
        arq = fopen(nome, "w+b");
    }
    return arq;
}
 
 
void exibirPaciente(Tno *raiz, char n[], FILE *arq) {
    Tpaciente aux;
    int resp;
    resp = buscar(n, raiz);
    if (resp == -1)
        printf("Cliente nao cadastrado.\n");
    else {
        fseek(arq, resp * sizeof(Tpaciente), 0);
        resp = fread(&aux, sizeof(Tpaciente), 1, arq);
        if (resp != 1)
            printf("Erro de leitura.\n");
        else {
            printf("Nome: %s\n", aux.nome);
            printf("Telefone: %s\n", aux.tel);
            printf("Email: %s\n", aux.email);
        }
    }
}
 
void alterarPaciente(Tno **raiz, char n[], FILE *arq) {
    Tpaciente aux;
    int resp, resp2, status;
    char op;
    resp = buscar(n, *raiz);
    if (resp == -1)
        printf("Cliente nao cadastrado.\n");
    else {
        fseek(arq, resp * sizeof(Tpaciente), 0);
        status = fread(&aux, sizeof(Tpaciente), 1, arq);
        if (status != 1)
            printf("Erro de leitura.\n");
        else {
            do {
                printf("\t\t--Alteracao--\n\n\n1 - Nome\n2 - Telefone\n3 - Email\n4 - Voltar\n");
                op = getch(); fflush(stdin);
                switch (op) {
                case '1':
                    printf("Digite o novo nome.\n"); //validar
                    pegarNome(n);
                    formatarNome(n);
                    strcpy(aux.nome, n);
                    break;
                case'2':
                    printf("Digite o novo telefone.\n");
                    pegarTel(n);
                    strcpy(aux.tel, n);
                    break;
                case'3':
                    printf("Digite o novo email.\n");
                    pegarEmail(n);
                    strcpy(aux.email, n);
                    break;
                case'4':
                    break;
                default:
                    printf("Opcao invalida.\n");
                    break;
                }
            } while (op != '4');
            fseek(arq, resp * sizeof(Tpaciente), 0);
            status = fwrite(&aux, sizeof(Tpaciente), 1, arq);
            if (status != 1)
                printf("Erro na gravacao.\n");
            else
                printf("Contato alterado com sucesso.\n");
        }
    }
}
 
void removerPaciente(Tno **raiz, char n[], FILE *arq) {
    Tpaciente aux;
    int resp, status;
    resp = buscar(n, *raiz);
    if (resp == -1)
        printf("Contato nao cadastrado.\n");
    else {
        fseek(arq, resp * sizeof(Tpaciente), 0);
        status = fread(&aux, sizeof(Tpaciente), 1, arq);
        do {
            printf("Deseja deletar o cliente '%s'(S/N)?\n", aux.nome);
            resp = toupper(getche());
        } while (resp != 'S' && resp != 'N');
        printf("\n");
        if (resp == 'S') {
            if (status != 1)
                printf("Erro de leitura.\n");
            else {
                aux.status = 0;
                fseek(arq, -1 * (int)sizeof(Tpaciente), 1);
                status = fwrite(&aux, sizeof(Tpaciente), 1, arq);
                if (status != 1)
                    printf("Erro de gravacao \n");
                else {
                    printf("Cliente '%s' removido com sucesso \n", aux.nome);
                    remover(raiz, n);
                }
            }
        }
    }
}
 
void cadastrarPaciente(Tno **raiz, char n[], FILE *arq) {
    Tpaciente aux;
    int pos, resp;
    fseek(arq, 0, 2);
    resp = buscar(n, *raiz);
    if (resp == -1) {
        fseek(arq, 0, 2);
        strcpy(aux.cpf, n);
        printf("Informe o nome.\n");
        pegarNome(aux.nome);
        formatarNome(aux.nome);
        printf("Informe o telefone.\n");
        pegarTel(aux.tel);
        printf("Informe o email.\n");
        pegarEmail(aux.email);
        aux.status = 1;
        resp = fwrite(&aux, sizeof(Tpaciente), 1, arq);
        if (resp != 1)
            printf("erro de gravacao.\n");
        else {
            printf("Contato cadastrado com sucesso.\n");
            pos = ftell(arq) / sizeof(Tpaciente) - 1;
            insert(raiz, aux.cpf, pos);
            return 1;
        }
    }
    else {
        printf("Paciente ja cadastrado.\n");
    }
}
 
void manutencao(FILE *arq, char nome[]) {
    FILE *arq2;
    Tpaciente aux;
    char n[] = "copia";
    int pos = 0;
    arq2 = criarArquivo(n);
    fseek(arq, 0, 0);
    if (arq2 == NULL)
        printf("Impossivel realizar manutencao.\n");
    else {
        while (1) {
            pos = fread(&aux, sizeof(Tpaciente), 1, arq);
            if (pos != 1) {
                if (!feof(arq))
                    printf("Erro na leitura.\n");
                else
                    printf("Manutencao feita.\n");
                break;
            }
            else {
                if (aux.status == 1) {
                    pos = fwrite(&aux, sizeof(Tpaciente), 1, arq2);
                    if (pos != 1) {
                        printf("Erro ao copiar.\n");
                    }
                }
            }
        }
        fclose(arq);
        remove(nome);
        fclose(arq2);
        rename(n, nome);
        return;
    }
    fclose(arq);
}
 
int buscarNome(FILE * arq, char nomeAux[], int aux) {
    int cont = -1, status;
    Tpaciente c;
 
    fseek(arq, aux, 0);
    while (1) {
        status = fread(&c, sizeof(Tpaciente), 1, arq);
        if (status != 1) {
            if (!feof(arq))
                return -2;
            else
                return -1;
        }
        else {
            if (c.status == 1 && strcmp(c.nome, nomeAux) == 0)
                return ftell(arq) / sizeof(Tpaciente) - 1;
        }
    }
}
void manutencaoC(FILE *arq, char nome[]) {
    FILE *arq2;
    Tpaciente aux;
    char n[] = "copia";
    int pos;
    fseek(arq, 0, 0);
    arq2 = criarArquivo(n);
    if (arq2 == NULL)
        printf("Impossivel realizar manutencao.\n");
    else {
        while (1) {
            pos = fread(&aux, sizeof(Tpaciente), 1, arq);
            if (pos != 1) {
                if (!feof(arq))
                    printf("Erro na leitura.\n");
                else
                    printf("Manutencao feita.\n");
                break;
            }
            else {
                if (aux.status == 1) {
                    pos = fwrite(&aux, sizeof(Tpaciente), 1, arq2);
                    if (pos != 1) {
                        printf("Erro ao copiar.\n");
                    }
                }
            }
        }
        fclose(arq);
        remove(nome);
        fclose(arq2);
        rename(n, nome);
        return;
    }
    fclose(arq);
}
#include "medicos.h"
 
void exibirMatriz(int matriz[5][2]) {
    int i, j;
    printf("\tSegunda-feira");
    printf("\tTerca-feira");
    printf("\tQuarta-feira");
    printf("\tQuinta-feira");
    printf("\tSexta-feira|\n");
    for (j = 0; j < 2; j = j + 1) {
        if (j == 0)
            printf("Manha: ");
        else
            printf("Tarde: ");
        for (i = 0; i < 5; i = i + 1) {
            if (matriz[i][j] == 1)
                printf("\t\tX");
            else
                printf("\t\t ");
        }
        printf("\n\n");
    }
}
void menuEspecialidades() {
    printf("1-Cardiologista.\n2-Dermatologista.\n3-Ginecologista.\n4-Pediatra.\n5-Clinico geral\n");
}
void exibirMedico(Tno *raiz, char n[], FILE *arq) {
    Tmedicos aux;
    int resp;
    fseek(arq, 0, 2);
    resp = buscar(n, raiz);
    if (resp == -1)
        printf("Cliente nao cadastrado.\n");
    else {
        fseek(arq, resp * sizeof(Tmedicos), 0);
        resp = fread(&aux, sizeof(Tmedicos), 1, arq);
        if (resp != 1)
            printf("Erro de leitura.\n");
        else {
            printf("Nome: %s\n", aux.nome);
            printf("Telefone: %s\n", aux.tel);
            printf("Email: %s\n", aux.email);
            printf("CRM: %s\n", aux.crm);
            if (aux.especialidade == 1)
                printf("Especialidade: ortopedista.\n");
            else if (aux.especialidade == 2)
                printf("Especialidade: dermatologista.\n");
            else if (aux.especialidade == 3)
                printf("Especialidade: ginecologista.\n");
            else if (aux.especialidade == 4)
                printf("Especialidade: pediatra.\n");
            else
                printf("Especialidade: clinico geral.\n");
            exibirMatriz(aux.horario);
        }
    }
}
 
void alterarMedico(Tno **raiz, char n[], FILE *arq) {
    Tmedicos aux;
    int resp, resp2, status, respi, respj;
    char op, resposta;
    fseek(arq, 0, 0);
    resp = buscar(n, *raiz);
    if (resp == -1)
        printf("Medico nao cadastrado.\n");
    else {
        fseek(arq, resp * sizeof(Tmedicos), 0);
        status = fread(&aux, sizeof(Tmedicos), 1, arq);
        if (status != 1)
            printf("Erro de leitura.\n");
        else {
            do {
                printf("O que deseja alterar?\n");
                printf("1 - Nome\n2 - Telefone\n3 - Email\n4 - Especialidade\n5 - Horario\n6 - Sair\n");
                op = getche(); fflush(stdin);
                printf("\n");
                switch (op) {
                case '1':
                    printf("Digite o novo nome.\n");
                    pegarNome(aux.nome);
                    formatarNome(aux.nome);
                    break;
                case'2':
                    printf("Digite o novo telefone.\n");
                    pegarTel(aux.tel);
                    break;
                case'3':
                    printf("Digite o novo email.\n");
                    pegarEmail(aux.email);
                    break;
                case'4':
                    printf("Informe nova especialidade.");
                    menuEspecialidades();
                    scanf("%d", &aux.especialidade); fflush(stdin);
                    while (aux.especialidade < 1 || aux.especialidade > 5) {
                        printf("Selecione uma especialidade valida:");
                        menuEspecialidades();
                        scanf("%d", &aux.especialidade); fflush(stdin);
                    }
                    break;
                case'5':
                    printf("Selecione os novos horarios.\n");
                    do {
                        do {
                            printf("1 - Segunda-feira.\n2 - Terca-feira.\n3 - Quarta-feira.\n4 - Quinta-feira.\n5 - Sexta-feira\n");
                            scanf_s("%d", &respi);
                        } while (respi < 1 || respi >6);
                        respi = respi - 1;
                        do {
                            printf("1 - Manha.\n2 - Tarde\n");
                            scanf_s("%d", &respj);
                        } while (respj < 1 || respj>2);
                        respj = respj - 1;
                        aux.horario[respi][respj] = 1;
                        printf("Informar outro horario(s/n(?\n");
                        resposta = toupper(getche());
                    } while (resposta != 'N');
                    break;
                case'6':
                    break;
                default:
                    printf("Opcao invalida.\n");
                    break;
                }
            } while (op != '6');
            fseek(arq, resp * sizeof(Tmedicos), 0);
            status = fwrite(&aux, sizeof(Tmedicos), 1, arq);
            if (status != 1)
                printf("Erro na gravacao.\n");
            else
                printf("Contato alterado com sucesso.\n");
        }
    }
}
 
void removerMedico(Tno **raiz, char n[], FILE *arq) {
    Tmedicos aux;
    int resp, status;
    fseek(arq, 0, 2);
    resp = buscar(n, *raiz);
    if (resp == -1)
        printf("Contato nao cadastrado.\n");
    else {
        fseek(arq, resp * sizeof(Tmedicos), 0);
        status = fread(&aux, sizeof(Tmedicos), 1, arq);
        if (status != 1)
            printf("Erro de leitura.\n");
        else {
            aux.status = 0;
            fseek(arq, -1 * (int)sizeof(Tmedicos), 1);
            status = fwrite(&aux, sizeof(Tmedicos), 1, arq);
            if (status != 1)
                printf("Erro de gravacao \n");
            else {
                printf("Contato removido com sucesso \n");
                remover(raiz, n);
            }
        }
    }
}
 
void cadastrarMedico(Tno **raiz, char n[], FILE *arq) {
    Tmedicos aux;
    int pos, resp, resp2, respi, respj, horario[5][2];
    char resposta;
    fseek(arq, 0, 2);
    resp = buscar(n, *raiz);
    if (resp == -1) {
        fseek(arq, 0, 2);
        strcpy(aux.crm, n);
        printf("Informe o nome.\n");
        pegarNome(aux.nome);
        formatarNome(aux.nome);
        printf("Informe o telefone.\n");
        pegarTel(aux.tel);
        printf("Informe o email.\n");
        pegarEmail(aux.email);
        printf("Selecione especialidade:\n");
        menuEspecialidades();
        scanf("%d", &aux.especialidade); fflush(stdin);
        while (aux.especialidade < 1 || aux.especialidade > 5) {
            printf("Selecione uma especialidade valida:");
            menuEspecialidades();
            scanf("%d", &aux.especialidade); fflush(stdin);
        }
        printf("Selecione os horarios.\n");
        pegarHorario(aux.horario);
        aux.status = 1;
        resp = fwrite(&aux, sizeof(Tmedicos), 1, arq);
        if (resp != 1)
            printf("Erro de gravacao.\n");
        else {
            printf("Medico cadastrado com sucesso.\n");
            pos = ftell(arq) / sizeof(Tmedicos) - 1;
            insert(&(*raiz), aux.crm, pos);
        }
    }
    else {
        printf("Paciente ja cadastrado.\n");
    }
}
 
void manutencaoM(FILE *arq, char nome[]) {
    FILE *arq2;
    Tmedicos aux;
    char n[] = "copia";
    int pos;
    fseek(arq, 0, 0);
    arq2 = criarArquivo(n);
    if (arq2 == NULL)
        printf("Impossivel realizar manutencao.\n");
    else {
        while (1) {
            pos = fread(&aux, sizeof(Tmedicos), 1, arq);
            if (pos != 1) {
                if (!feof(arq))
                    printf("Erro na leitura.\n");
                else
                    printf("Manutencao feita.\n");
                break;
            }
            else {
                if (aux.status == 1) {
                    pos = fwrite(&aux, sizeof(Tmedicos), 1, arq2);
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
 
int buscarNomeM(FILE * arq, char nomeAux[], int aux) {
    int cont = -1, status;
    Tmedicos c;
 
    fseek(arq, aux, 0);
    while (1) {
        status = fread(&c, sizeof(Tmedicos), 1, arq);
        if (status != 1) {
            if (!feof(arq))
                return -2; // erro de leitura
            else
                return -1; // nao achou
        }
        else {
            if (c.status == 1 && strcmp(c.nome, nomeAux) == 0)
                return ftell(arq) / sizeof(Tmedicos) - 1;
        }
    }
}
 
void buscaEspecialidade(FILE *arq, int especialidade) {
    Tmedicos aux;
    int status, cont = 0;
    fseek(arq, 0, 0);
    while (1) {
        status = fread(&aux, sizeof(Tmedicos), 1, arq);
        if (status != 1) {
            if (!feof(arq))
                printf("Erro de leitura.\n");
            else {
                if (cont = 0)
                    printf("Medico nao encontrado.\n");
            }
            break;
        }
        else{
            if (especialidade == aux.especialidade) {
                if(aux.status == 1){
                    cont = cont + 1;
                    printf("Nome: %s\nCRM:%s\n\n", aux.nome, aux.crm);
                    exibirMatriz(aux.horario);
                    printf("\n\n");
                }
            }
        }
    }
}
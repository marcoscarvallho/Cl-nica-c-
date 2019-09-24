#include"clientes.h"
#include"validacao.h"
#include"tree.h"
#include"medicos.h"
#include "types.h"
#include"consulta.h"
 
int main() {
    Tno *raiz = NULL, *raizM = NULL;
    FILE *arq , *arq2, *arq3;
    char n[] = "cliente.dat";
    char nm[] = "medico.dat";
    char no[] = "consulta.dat";
    char op, op1, op2, op3, cpf[CP], crm[CR], nome[T], respo;
    int resp, cont = 0, aux = 0, especialidade, resposta, i;
    Tpaciente aux2;
    Tmedicos aux3;
    Tdata data;
    arq = criarArquivo(n);
    setArvoreC(&raiz, arq);
    arq2 = criarArquivo(nm);
    setArvoreM(&raizM, arq2);
    arq3 = criarArquivo(no);
    data.ano = NULL;
    data.dia = NULL;
    data.mes = NULL;
    printf("\t\t--Bem-vindo--\n\n\n\n");
    do {
        printf("\t\t--Menu Principal--\n\n\n\n");
        printf("1 - Clientes.\n2 - Medicos\n3 - Sair.\n");
        op = getche(); fflush(stdin);
        printf("\n");
        system("cls");
        switch (op) {
        case'1':
            do {
                printf("\t\t--CLIENTES--\n\n\n1 - Cadastrar.\n2 - Marcar consulta.\n3 - Consultas do paciente.\n4 - Remover\n5 - Alterar dados.\n6 - Exibir dados por nome.\n7 - Exibir dados por CPF.\n8 - Proxima pagina.\n9 - Voltar\n\n");
                op1 = getche(); fflush(stdin);
                printf("\n");
                switch (op1) {
                case'1':
                    printf("Informe o cpf.\n");
                    pegarCPF(cpf); fflush(stdin);
                    cadastrarPaciente(&raiz, cpf, arq);
                    system("pause>nul");
                    break;
                case'2':
                    printf("Informe o cpf.\n");
                    pegarCPF(cpf);
                    printf("Informe o CRM.\n");
                    pegarCRM(crm);
                    printf("Informe a data.\n");
                    i = 0;
                    do{
                        if (i>0)
                            printf("Data invalida.\nDigite novamente:\n");
                        printf("Digite o dia.\n");
                        scanf("%d", &data.dia);
                        printf("Digite o mes.\n");
                        scanf("%d", &data.mes);
                        printf("Digite o ano.\n");
                        scanf("%d", &data.ano);
                        resp = validarData(data);
                        i = 1;
                    }while (resp == 0);
                    i = 0;
                    do{
                        if(i>0)
                            printf("Turno invalido.Digite novamente\n");
                        printf("Informe o turno.\n1 - Manha.\n2 - Tarde\n");
                        respo = getche();fflush(stdin);
                        i = 1;
                    }while(respo != '1' && respo != '2');
                    resposta = buscar(cpf, raiz);
                    if(resposta != -1){
                        resposta = buscar(crm, raizM);
                    }
                    if(resposta != -1){
                        marcar(cpf, crm, data, respo, arq3);
                    }
                    system("pause>nul");
                    break;
                case'3':
                    printf("Informe o CPF.\n");
                    pegarCPF(crm);
                    resp = buscar(cpf, raiz);
                    if(resp == -1)
                        break;
                    do{
                        printf("Digite o dia.\n");
                        scanf("%d", &data.dia);
                        printf("Digite o mes.\n");
                        scanf("%d", &data.mes);
                        printf("Digite o ano.\n");
                        scanf("%d", &data.ano);
                        resp = validarData(data);
                        if(resp==0)
                            printf("Data invalida.\nDigite novamente:\n");
                    }while (resp == 0);
                    do{
                        printf("Informe o turno.\n1 - Manha.\n2 - Tarde\n");
                        respo = getche();fflush(stdin);
                    }while(respo != '1' && respo != '2');
                    Consultas(cpf, arq3, arq2, raizM);
                    system("pause>nul");
                    break;
                case'4':
                    printf("Informe o cpf.\n");
                    pegarCPF(cpf); fflush(stdin);
                    removerPaciente(&raiz, cpf, arq);
                    system("pause>nul");
                    break;
                case'5':
                    printf("Informe o cpf.\n");
                    pegarCPF(cpf); fflush(stdin);
                    alterarPaciente(&raiz, cpf, arq);
                    system("pause>nul");
                    break;
                case'6':
                    printf("Informe o nome.\n");
                    pegarNome(nome); fflush(stdin);
                    formatarNome(nome);
                    while (1) {
                        resp = buscarNome(arq, nome, aux);
                        if (resp == -1) {
                            printf("Cliente nao encontrado.\n");
                            break;
                        }
                        else if (resp == -2) {
                            printf("erro.\n");
                            break;
                        }
                        else {
                            fseek(arq, aux * sizeof(Tpaciente), 0);
                            resp = fread(&aux2, sizeof(Tpaciente), 1, arq);
                            if (resp != 1)
                                printf("Erro de leitura.\n");
                            else {
                                printf("Nome: %s\nTelefone: %s\nEmail: %s\nCPF:", aux2.nome, aux2.tel, aux2.email);
                                for (resp = 0; resp < CP - 1; resp = resp + 1) {
                                    printf("%c", aux2.cpf[resp]);
                                    if (resp == 2 || resp == 5)
                                        printf(".");
                                    if (resp == 8)
                                        printf("-");
                                }
                                printf("\n");
                                cont++;
                            }
                        }
                        aux = aux + 1;
                        fflush(stdin);
                    }
                    system("pause>nul");
                    aux = 0;
                    break;
                case'7':
                    printf("Informe o cpf.\n");
                    pegarCPF(cpf);
                    exibirPaciente(raiz, cpf, arq);
                    system("pause>nul");
                    break;
                case'8':
                    do{
                        system("cls");
                        printf("\t\t--CLIENTES--\n\n\n1 - Consultar CPF.\n2 - Desmarcar consulta.\n3 - Pagina anterior.\n4 - voltar.\n");
                        op3 = getche(); fflush(stdin);
                        printf("\n");
                        switch(op3){
                        case'1':
                            printf("Informe o cpf.\n");
                            pegarCPF(cpf);
                            resp = buscar(cpf, raiz);
                            if (resp != -1)
                                printf("Paciente cadastrado.\n");
                            else
                                printf("Paciente nao cadastrado.\n");
                            fflush(stdin);
                            system("pause>nul");
                            break;
                        case'2':
                            printf("Informe o cpf.\n");
                            pegarCPF(cpf);
                            printf("Informe o CRM.\n");
                            pegarCRM(crm);
                            printf("Informe a data.\n");
                            i = 0;
                            do{
                                if (i>0)
                                    printf("Data invalida.\nDigite novamente:\n");
                                printf("Digite o dia.\n");
                                scanf("%d", &data.dia);
                                printf("Digite o mes.\n");
                                scanf("%d", &data.mes);
                                printf("Digite o ano.\n");
                                scanf("%d", &data.ano);
                                resp = validarData(data);
                                i = 1;
                            }while (resp == 0);
                            do{
                                printf("Informe o turno.\n1 - Manha.\n2 - Tarde\n");
                                respo = getche();fflush(stdin);
                            }while(respo != '1' && respo != '2');
                            resposta = buscar(cpf, raiz);
                            if(resposta != -1){
                                resposta = buscar(crm, raizM);
                            }
                            if(resposta != -1){
                                desmarcar(cpf, crm, data, respo, arq3);
                            }
                            system("pause>nul");
                            break;
                        case'3':
                            break;
                        case'4':
                            break;
                        default:
                            printf("Opcao invalida.\n");
                            break;
                        }
 
                    }while(op3 != '4' && op3 != '3');
                    if (op3 == '4')
                        op1 = '9';
                    system("pause>nul");
                    break;
                case'9':
                    break;
                default:
                    printf("Opcao invalida.\n");
                    system("pause>nul");
                    break;
                }
                system("cls");
            } while (op1 != '9');
            break;
        case'2':
            do {
                printf("\t\t--MEDICOS--\n\n\n1 - Cadastrar.\n2 - Consultar por CRM.\n3 - Remover\n4 - Alterar dados.\n");
                printf("5 - Exibir dados por nome.\n6 - Exibir dados por CRM.\n7 - Buscar por especialidade\n8 - Exibir pacientes da data\n9 - Sair\n");
                op2 = getche(); fflush(stdin);
                printf("\n");
                switch (op2) {
                case'1':
                    printf("Informe o CRM.\n");
                    pegarCRM(crm);
                    cadastrarMedico(&raizM, crm, arq2);
                    system("pause>nul");
                    break;
                case'2':
                    printf("Informe o CRM.\n");
                    pegarCRM(crm);
                    resp = buscar(crm, raizM);
                    if (resp != -1)
                        printf("Medico cadastrado.\n");
                    else
                        printf("Medico nao cadastrado.\n");
                    fflush(stdin);
                    system("pause>nul");
                    break;
                case'3':
                    printf("Informe o crm.\n");
                    pegarCRM(crm);
                    removerMedico(&raizM, crm, arq2);
                    fflush(stdin);
                    system("pause>nul");
                    break;
                case'4':
                    printf("Informe o crm.\n");
                    pegarCRM(crm);
                    alterarMedico(&raizM, crm, arq2);
                    fflush(stdin);
                    system("pause>nul");
                    break;
                case'5':
                    fseek(arq2, 0, 0);
                    printf("Informe o nome.\n");
                    cont = 0;
                    pegarNome(nome);
                    formatarNome(nome);
                    while (1) {
                        resp = buscarNomeM(arq2, nome, aux);
                        if (resp == -1) {
                            if(cont == 0){
                                printf("Medico nao encontrado.\n");
                            }
                            break;
                        }
                        else {
                            fseek(arq2, resp * sizeof(Tmedicos), 0);
                            aux = resp + sizeof(Tmedicos);
                            resp = fread(&aux3, sizeof(Tmedicos), 1, arq2);
                            if (resp != 1)
                                printf("Erro de leitura.\n");
                            else if (aux3.status == 1) {
                                printf("Nome: %s\nTelefone: %s\nEmail: %s\nCRM: %s\n", aux3.nome, aux3.tel, aux3.email, aux3.crm);
                                if (aux3.especialidade == 1)
                                    printf("Especialidade: Ortopedista.\n");
                                else if (aux3.especialidade == 2)
                                    printf("Especialidade: Dermatologista.\n");
                                else if (aux3.especialidade == 3)
                                    printf("Especialidade: Ginecologista.\n");
                                else if (aux3.especialidade == 4)
                                    printf("Especialidade: Pediatra.\n");
                                else
                                    printf("Especialidade: Clinico geral.\n");
                                exibirMatriz(aux3.horario);
                                cont++;
                            }
                        }
                    }
                    aux = 0;
                    fflush(stdin);
                    system("pause>nul");
                    break;
                case'6':
                    printf("Informe o CRM.\n");
                    pegarCRM(crm);
                    exibirMedico(raizM, crm, arq2);
                    fflush(stdin);
                    system("pause>nul");
                    break;
                case'7':
                    printf("Selecione especialidade:\n");
                    menuEspecialidades();
                    scanf("%d", &especialidade); fflush(stdin);
                    while (especialidade < 1 || especialidade > 5) {
                        printf("Selecione uma especialidade valida:");
                        menuEspecialidades();
                        scanf("%d", &especialidade); fflush(stdin);
                    }
                    buscaEspecialidade(arq2, especialidade);
                    system("pause>nul");
                    break;
                case'8':
                    printf("Informe o CRM.\n");
                    pegarCRM(crm);
                    resp = buscar(crm, raizM);
                    if(resp == -1)
                        break;
                    do{
                        printf("Digite o dia.\n");
                        scanf("%d", &data.dia);
                        printf("Digite o mes.\n");
                        scanf("%d", &data.mes);
                        printf("Digite o ano.\n");
                        scanf("%d", &data.ano);
                        resp = validarData(data);
                        if(resp==0)
                            printf("Data invalida.\nDigite novamente:\n");
                    }while (resp == 0);
                    do{
                        printf("Informe o turno.\n1 - Manha.\n2 - Tarde\n");
                        respo = getche();fflush(stdin);
                    }while(respo != '1' && respo != '2');
 
                    Pacientes(crm, data, respo, arq3, raiz, arq);
                    system("pause>nul");
                    break;
                case'9':
                    break;
                default:
                    printf("Opcao invalida.\n");
                    system("pause>nul");
                    break;
                }
                system("cls");
            } while (op2 != '9');
 
            break;
        case'3':
            break;
        }
    }while (op != '3');
 
 
    manutencaoM(arq2, nm);
    manutencaoC(arq, n);
    fclose(arq3);
    deletar(&raizM);
    deletar(&raiz);
    system("pause");
    return 0;
 
}
#include"consulta.h"
#include"tree.h"
#include"medicos.h"
#include"clientes.h"
#include"types.h"
#include"validacao.h"
 
void  Pacientes(char crm[], Tdata d, int turno, FILE *arqC, Tno *raiz, FILE *arqP){
    Tconsultas aux;
    Tpaciente p;
    Tdata dataAux;
    int status, pos, statusP;
    fseek(arqC, 0, 0);
    while(1){
        status = fread(&aux, sizeof(Tconsultas), 1, arqC);
        if(status != 1){
            if(!feof(arqC))
                printf("Erro de leitura.\n");
            else
                printf("Nao ha pacientes agendados.\n");
            break;
        }
        else{
            dataAux = aux.data;
            if((aux.data.ano == d.ano) && (aux.data.dia == d.dia) && (aux.data.mes == d.mes) && (aux.turno == turno)){
                pos = buscar(aux.cpf, raiz);
                fseek(arqP, pos * sizeof(Tpaciente),0);
                statusP = fread(&p, sizeof(Tpaciente), 1, arqP);
                if(statusP != 1)
                    printf("Erro de leitura.\n");
                else
                    printf("Paciente: %s \n", p.nome);
            }
        }
    }
}
 
void Consultas (char cpf[], FILE *arqC, FILE *arqM, Tno *raiz){
    Tconsultas auxC;
    Tmedicos m;
    int status, statusM, pos;
    fseek(arqC,  0, 0);
    while(1){
        status = fread(&auxC, sizeof(Tconsultas), 1, arqC);
        if(status != 1){
            if(!feof(arqC))
                printf("Erro de leitura.\n");
            else
                printf("Nao ha consultas agendados.\n");
            break;
        }
        else{
            if(auxC.cpf == cpf && auxC.status == 1){
                pos = buscar(auxC.crm, raiz);
                fseek(arqM, pos * sizeof(Tmedicos),0);
                status = fread(&m, sizeof(Tmedicos), 1, arqM);
                if(status != 1)
                    printf("Erro de leitura.\n");
                else{
                    printf("Medico: %s \n", m.nome);
                    printf("Crm: %s \n", m.crm);
                    if(m.especialidade == 1)
                        printf("Especialidade: Cardiologista\n" );
                    else if(m.especialidade == 2)
                        printf("Especialidade: Dermatologista\n" );
                    else if(m.especialidade == 3)
                        printf("Especialidade: Ginecologista\n" );
                    else if(m.especialidade == 4)
                        printf("Especialidade: Pediatra\n" );
                    else
                        printf("Especialidade: Clinico geral\n" );
                    printf("Data: %d/%d/%d \n", auxC.data.dia, auxC.data.mes, auxC.data.ano);
                    if(auxC.turno == 'M')
                        printf("Turno: manha\n");
                    else
                        printf("Turno: tarde\n");
 
                }
            }
        }
    }
}
 
void marcar(char cpf[], char crm[], Tdata data, char turno, FILE *arq){
    int cont = 0, status;
    Tconsultas aux;
    char resp;
    fseek(arq, 0, 0);
    while(1){
        status = fread(&aux, sizeof(Tconsultas), 1, arq);
        if(status != 1){
            if(!feof)
                printf("Erro de leitura.\n");
        }
        else{
            if(strcmp(aux.crm,crm) == 0 && aux.data.dia == data.dia && aux.data.mes == data.mes && aux.data.ano == 0 && aux.turno == turno)
                cont++;
        }
    }
    if(cont < 10){
        strcpy(aux.cpf, cpf);
        strcpy(aux.crm, crm);
        aux.data.dia = data.dia;
        aux.data.mes = data.mes;
        aux.data.ano = data.ano;
        aux.turno = turno;
        aux.status = 1;
        fseek(arq, 0, 2);
        status = fwrite(&aux, sizeof(Tconsultas), 1, arq);
        if(status != 1)
            printf("Erro de leitura.\n");
        else
            printf("Consulta agendada com sucesso.\n");
    }
    else{
        printf("Entrar na fila de espera?(Use S ou N)\n");
        resp = getchar(); fflush(stdin);
        resp = toupper(resp);
        while(resp != 'N' && resp != 'S'){
            printf("Resposta invalida.\n");
            resp = getchar(); fflush(stdin);
        }
        if(resp == 'S'){
            strcpy(aux.cpf, cpf);
            strcpy(aux.crm, crm);
            aux.data = data;
            aux.turno = turno;
            aux.status = 3;
            fseek(arq, 0, 2);
            status = fwrite(&aux, sizeof(Tconsultas), 1, arq);
            if(status != 1)
                printf("Erro de leitura.\n");
            else
                printf("Entrou na fila com sucesso.\n");
        }
    }
 
}
int desmarcar(char cpf[], char crm[], Tdata data, char turno, FILE *arq){
    int cont = 0, status, i;
    Tconsultas aux;
    fseek(arq, 0, 0);
    while(1){
        status = fread(&aux, sizeof(Tconsultas), 1, arq);
        if(status != 1){
            if(!feof(arq))
                printf("Erro de leitura.\n");
            else
                printf("Nao encontrado\n");
            return 0;
        }
        else{
            if(strcmp(aux.crm,crm) == 0 && aux.data.dia == data.dia && aux.data.mes == data.mes && aux.data.ano == data.ano && aux.turno ==turno && aux.status == 1 && strcmp(aux.cpf,cpf)==0){
                aux.status = -1;
                status = fseek(arq, -sizeof(Tconsultas), 1);
                if(status!=1 ){
                    printf("Erro de leitura.\n");
                    return 0;
                }
                fwrite(&aux,sizeof(Tconsultas),1,arq);
                if(status!=1 ){
                    printf("Erro de leitura.\n");
                    return 0;
                }
                cont = 0;
                while(1){
                    status = fread(&aux, sizeof(Tconsultas),1,arq);
                    if(status != 1){
                        if(!feof(arq))
                            printf("Erro de leitura.\n");
                        else if(cont == 0)
                            printf("Nao encontrado\n");
                        return 0;
                    }
                    else{
                        if(aux.status == 3 && strcmp(aux.crm,crm) == 0 && aux.data.dia == data.dia && aux.data.mes == data.mes &&aux.data.ano == data.ano && aux.turno == turno && aux.status == 1){
                            cont = cont + 1;
                            aux.status = 1;
                            status = fseek(arq, -sizeof(Tconsultas), 1);
                            if(status!=1 ){
                                printf("Erro de leitura.\n");
                                return 0;
                            }
                            fwrite(&aux,sizeof(Tconsultas),1,arq);
                            if(status!=1 ){
                                printf("Erro de leitura.\n");
                                return 0;
                            }
                        }
                    }
                }
                return i;
            }
        }
    }
}
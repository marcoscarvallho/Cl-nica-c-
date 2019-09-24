#include"types.h"
 
int pegarNome(char n[]) {
    int i = 0, cont = 0, resp;
    char op = 'S';
    do {
        if (i != 0)
            printf("Digite novamente.\n");
        for (i = 0; i < T - 1; i = i + 1) {
            n[i] = getche(); fflush(stdin);
            if (n[i] == 13) {
                n[i] = '\0';
                break;
            }
            if (isspace(n[i]) != 0) {
                if (i == 0)
                    i = i - 1;
                else if (cont != 0) {
                    i = i - 1;
                }
                else
                    cont = cont + 1;
            }
            else
                cont = 0;
        }
        printf("\n");
        resp = validaNome(n);
    } while (resp == 0);
}
 
int validaNome(char n[]) {
    int i;
    for (i = 0; i < strlen(n); i = i + 1) {
        if (!isalpha(n[i]) && !isspace(n[i])) {
            return 0;
        }
    }
    return 1;
 
}
 
void formatarNome(char n[]) {
    int i;
    for (i = 0; i < strlen(n); i = i + 1) {
        if (i == 0 || isspace(n[i - 1]) != 0)
            n[i] = toupper(n[i]);
        else
            n[i] = tolower(n[i]);
    }
}
 
void pegarTel(char n[]) {
    int i = 0, resp;
    char op = 'S';
    do {
        if (i != 0)
            printf("Digite novamente\n");
        for (i = 0; i < t - 1; i = i + 1) {
            n[i] = getche();
            if (n[i] == 13)
                break;
        }
        n[i] = '\0';
        printf("\n");
        resp = validaTel(n);
    } while (resp == 0);
}
 
int validaTel(char n[]) {
    int i, cont = 0;
    for (i = 0; i < strlen(n); i++) {
        cont = cont + 1;
        if (n[i] != '0' && n[i] != '1' && n[i] != '2' && n[i] != '3' && n[i] != '4' && n[i] != '5' && n[i] != '6' && n[i] != '7' && n[i] !='8' && n[i] != '9')
            return 0;
    }
    if (cont == t - 1 || cont == t - 7 || cont == t - 5 || cont == t - 6)
        return 1;
    else
        return 0;
}
 
void pegarEmail(char n[]) {
    int i = 0, resp;
    do {
        if (i != 0)
            printf("Digite novamente.\n");
        for (i = 0; i < T - 1; i = i + 1) {
            n[i] = getche();
            if (n[i] == 13) {
                n[i] = '\0';
                break;
            }
        }
        printf("\n");
        resp = validaEmail(n);
    } while (resp != 1);
}
 
int validaEmail(char n[]) {
    int i, cont = 0;
    for (i = 0; i < strlen(n); i++) {
        if (n[i] == '@') {
            cont++;
            if (cont > 1 || n[0] == '@')
                return 0;
        }
    }
    if (cont == 0)
        return 0;
    else
        return 1;
}
 
void pegarCPF(char n[]) {
    int i = 0, resp;
    do {
        if (i != 0)
            printf("Digite novamente.\n");
        for (i = 0; i < CP - 1; i = i + 1) {
            n[i] = getche(); fflush(stdin);
            if (n[i] == 13) {
                n[i] = '\0';
                break;
            }
            if (i == 2 || i == 5)
                printf(".");
            if (i == 8)
                printf("-");
        }
        printf("\n");
        n[11] = '\0';
        resp = validaCPF(n);
    } while (resp == 0);
}
 
int validaCPF(char cpf[]) {
    int i, j, digito1 = 0, digito2 = 0;
    if (strlen(cpf) != 11)
        return 0;
    else if ((strcmp(cpf, "00000000000") == 0) || (strcmp(cpf, "11111111111") == 0) || (strcmp(cpf, "22222222222") == 0) ||
        (strcmp(cpf, "33333333333") == 0) || (strcmp(cpf, "44444444444") == 0) || (strcmp(cpf, "55555555555") == 0) ||
        (strcmp(cpf, "66666666666") == 0) || (strcmp(cpf, "77777777777") == 0) || (strcmp(cpf, "88888888888") == 0) ||
        (strcmp(cpf, "99999999999") == 0))
        return 0;
    else
    {
        for (i = 0, j = 10; i < strlen(cpf) - 2; i++, j--)
            digito1 += (cpf[i] - 48) * j;
        digito1 %= 11;
        if (digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if ((cpf[9] - 48) != digito1)
            return 0;
        else
        {
            for (i = 0, j = 11; i < strlen(cpf) - 1; i++, j--)
                digito2 += (cpf[i] - 48) * j;
            digito2 %= 11;
            if (digito2 < 2)
                digito2 = 0;
            else
                digito2 = 11 - digito2;
            if ((cpf[10] - 48) != digito2)
                return 0;
        }
    }
    return 1;
}
 
void pegarCRM(char crm[]) {
    int i, resp=1;
    do{
        if (resp == 0){
            printf("Digite novamente.\n");
        }
        for (i = 0; i < 8; i = i + 1) {
            crm[i] = getche(); fflush(stdin);
            if (crm[i] == 13) {
                break;
            }
        }
        crm[0] = toupper(crm[0]);
        crm[1] = toupper(crm[1]);
        crm[i] = '\0';
        printf("\n");
        resp = validaCRM(crm);
    }while (resp == 0);
}
 
int validaCRM(char n[]) {
    int i, tam = strlen(n);
    if (tam < 2 || tam > 8) {
        return 0;
    }
    for (i = 2; i < tam; i++) {
        if (!isdigit(n[i]))
            return 0;
    }
    i = validaSigla(n);
    if (i == 0)
        return 0;
    return 1;
}
 
int validaSigla(char n[]) {
    char a[3];
    a[0] = toupper(n[0]);
    a[1] = toupper(n[1]);
    a[2] = '\0';
    if (strcmp("AM", a) == 0 || strcmp("AC", a) == 0 || strcmp("AL", a) == 0 || strcmp("AP", a) == 0 || strcmp("BA", a) == 0 || strcmp("CE",a) == 0 || strcmp("DF", a) == 0 || strcmp("ES", a) == 0 || strcmp("GO", a) == 0 || strcmp("MA", a) == 0 || strcmp("MT", a) == 0 ||strcmp("MS", a) == 0 || strcmp("MG", a) == 0 || strcmp("PA", a) == 0 || strcmp("PB", a) == 0 || strcmp("PR", a) == 0 || strcmp("PE", a) == 0|| strcmp("PI", a) == 0 || strcmp("RJ", a) == 0 || strcmp("RN", a) == 0 || strcmp("RS", a) == 0 || strcmp("RO", a) == 0 || strcmp("RR", a) ==0 || strcmp("SC", a) == 0 || strcmp("SP", a) == 0 || strcmp("SE", a) == 0 || strcmp("TO", a) == 0)
        return 1;
    return 0;
}
 
int anobissexto (Tdata dat){
    if(dat.ano%400==0 || (dat.ano%4 == 0 && dat.ano%100 != 0))
        return 1;
    else
        return 0;
}
 
void pegarData(Tdata data){
    int resp, i = 0;
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
}
 
int validarData(Tdata data){
    Tdata hoje;
    time_t tempo;
    struct tm *now;
    int resp;
    tempo = time(NULL);
    now = localtime(&tempo);
    hoje.dia = now->tm_mday;
    hoje.mes = now->tm_mon + 1;
    hoje.ano = now->tm_year+ 1900;
    if(data.mes == 1|| data.mes == 3|| data.mes ==5 || data.mes == 7 || data.mes == 8 || data.mes == 10 || data.mes == 12){
        if(data.dia < 1 || data.dia >31)
            resp = 0;
        else
            resp = 1;
    }
    else if(data.mes == 2){
        resp = anobissexto(data);
        if(resp == 0){
            if(data.dia < 1 || data.dia > 28)
                resp = 0;
            else
                resp = 1;
        }
        else{
            if(data.dia < 1 || data.dia > 28)
                resp = 0;
            else
                resp = 1;
        }
 
    }
    else{
        if(data.dia < 1 || data.dia > 30)
            resp = 0;
        else
            resp = 1;
    }
    if (resp == 1){
        if(data.dia == hoje.dia && data.mes == hoje.mes && data.ano == hoje.ano)
            resp = 1;
        else if(data.ano > hoje.ano || data.mes > hoje.mes && data.ano >= data.ano || data.dia > hoje.dia && data.mes > hoje.mes && data.ano>= hoje.ano)
            resp = 1;
        else
            resp = 0;
    }
    return resp;
}
 
int pegarHorario(int horario[5][2]){
    int respi, respj, resp;
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
        horario[respi][respj] = 1;
        printf("Informar outro horario?(s/n)\n");
        resp = toupper(getche()); fflush(stdin);
    } while (resp != 'N');
    return horario[5][2];
}
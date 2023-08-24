#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Structure to represent a file or folder
typedef struct nodo {
    char nome[100];
    int tipo; // 0 = arquivo, 1 = pasta
    struct nodo* pai;
    struct nodo* filho;
} Nodo;

typedef struct lista {
    Nodo* nodo;
    struct lista* prox;
    struct lista* ant;
} Lista;

void mostrarCaminho(Nodo* atual) {
    if (atual == NULL) {
        return;
    }
    
    mostrarCaminho(atual->pai);
    printf("->%s", atual->nome);
}

void mostrarConteudo(Nodo* atual) {
    //
}


void criarArquivo(Nodo* atual, char nome[]) {
    //
}

void copiarStr(char dest[], char orig[], int ini, int fim){
    int i=0, tam=strlen(orig);
    while(i+ini<tam && i<fim-ini && orig[i+ini] != '\0' && orig[i+ini] != '\n'){
        dest[i] = orig[i+ini];
        i++;
    }
    dest[i] = '\0';
}

int main(){
    Nodo *atual = malloc(sizeof(Nodo));
    strcpy(atual->nome, "raiz");
    atual->pai = NULL;
    atual->filho = NULL;

    char str[14],cmd[3], par[11];
    do{
        mostrarCaminho(atual);
        printf("\n");
        fflush(stdin);
        fgets(str, 100, stdin);
        copiarStr(cmd, str, 0, 2);
        copiarStr(par, str, 3, 13);
        printf("str: %s\ncmd: %s\npar: %s\n\n",str,cmd,par);
    }while(strcmp(cmd,"ex")!=0);
    return 0;
}
    

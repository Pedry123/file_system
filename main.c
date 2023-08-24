#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct nodo {
    char nome[100];
    int tipo;
    struct nodo *filho;
    struct nodo *pai;
} Nodo;

typedef struct pilha {
    Nodo* nodo;
    struct pilha *prox;
    struct pilha *ant;
} Pilha;

// Inserir nodo na pilha
Pilha* empilhar(Pilha *pilha, Nodo *nodo) {
    Pilha *novo = malloc(sizeof(Pilha));
    novo->nodo = nodo;
    novo->prox = pilha;
    novo->ant = NULL;
    if (pilha != NULL) {
        pilha->ant = novo;
    }
    return novo;
}

void desempilhar(Pilha *pilha) {
    if (pilha != NULL) {
        Pilha *aux = pilha;
        pilha = pilha->prox;
        free(aux);
    }
}

Nodo* criarArquivo(char nome[100], Nodo *pai, Pilha *pilha) {
    Nodo *nodo = malloc(sizeof(Nodo));
    strcpy(nodo->nome, nome);
    nodo->tipo = 0; // arquivo
    nodo->pai = pai;
    nodo->filho = NULL;
    return nodo;
}

void mostrarCaminho(Nodo *a) {
    printf("->%s\n", a->nome);
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
    Nodo *raiz = malloc(sizeof(Nodo));
    strcpy(raiz->nome, "");
    raiz->tipo = 1; // diretorio
    raiz->pai = NULL;
    raiz->filho = NULL;

    Nodo *atual = raiz;

    Pilha *pilhaAtual = malloc(sizeof(Pilha));
    pilhaAtual->nodo = NULL;
    pilhaAtual->prox = NULL;
    pilhaAtual->ant = NULL;

    char str[14],cmd[3], par[11];
    do{
        fflush(stdin);
        gets(str);
        copiarStr(cmd, str, 0, 2);
        copiarStr(par, str, 3, 13);
        if (strcmp(cmd, "ma")) {
            Nodo* arquivo = malloc(sizeof(Nodo));
            arquivo = criarArquivo(par, atual, pilhaAtual);
            pilhaAtual = empilhar(pilhaAtual, arquivo);
            //printf("str: %s\ncmd: %s\npar: %s\n\n",str,cmd,par);
            free(arquivo);
        }
        printf("%s", raiz->filho->nome); //dando null arrumar
    }while(strcmp(cmd,"ex")!=0);

    free(raiz);
    free(atual);
    free(pilhaAtual);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ARQUIVO 0
#define PASTA 1


typedef struct nodo {
    char nome[100];
    int tipo;
    struct nodo *ant;
    struct nodo *prox;
} Nodo;

typedef struct lista {
    Nodo *primeiro;
} Lista;

typedef struct nodoVertical {
    Nodo* pasta;
    Lista* lista;
    struct nodoVertical* ant;
    struct nodoVertical* prox;
} NodoVertical;

void copiarStr(char dest[], char orig[], int ini, int fim){
    int i=0, tam=strlen(orig);
    while(i+ini<tam && i<fim-ini && orig[i+ini] != '\0' && orig[i+ini] != '\n'){
        dest[i] = orig[i+ini];
        i++;
    }
    dest[i] = '\0';
}

Nodo* criarNodo(char nome[], int tipo){
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    strcpy(novo->nome, nome);
    novo->tipo = tipo;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

Nodo* inserirNodo(Nodo *nodo, char nome[], int tipo){
    Nodo *novo = criarNodo(nome, tipo);
    Nodo *aux = nodo;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = novo;
    novo->ant = aux;
    return novo;
}

Nodo* deletarNodo(Nodo *nodo){
    Nodo *aux = nodo->ant;
    if(aux != NULL){
        aux->prox = nodo->prox;
    }
    if(nodo->prox != NULL){
        nodo->prox->ant = aux;
    }
    free(nodo);
    return aux;
}

Nodo* buscarNodo(Nodo *nodo, char nome[]){
    Nodo *aux = nodo;
    while(aux != NULL){
        if(strcmp(aux->nome, nome) == 0){
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

Nodo* liberarNodo(Nodo *nodo){
    Nodo *aux = nodo;
    while(aux != NULL){
        Nodo *aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    return NULL;
}

void listarNodos(Nodo *nodo){
    Nodo *aux = nodo;
    while(aux != NULL){
        if (aux->tipo == PASTA) {
            printf("%s-\n",aux->nome);
        } else {
            printf("%s\n",aux->nome);
        }
        aux = aux->prox;
    }
}

Lista* criarLista(){
    Lista *lista = (Lista*) malloc(sizeof(Lista));
    lista->primeiro = NULL;
    return lista;
}

void inserirNodoNaLista(Lista *lista, char nome[], int tipo){
    Nodo *novo = criarNodo(nome, tipo);
    if (lista->primeiro == NULL) {
        lista->primeiro = novo;
    } else {
        Nodo *aux = lista->primeiro;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->ant = aux;
    }
}

void deletarNodoDaLista(Lista *lista, Nodo *nodo) {
    if (nodo->ant != NULL) {
        nodo->ant->prox = nodo->prox;
    }
    if (nodo->prox != NULL) {
        nodo->prox->ant = nodo->ant;
    }
    if (nodo == lista->primeiro) {
        lista->primeiro = nodo->prox;
    }
    free(nodo);
}

Lista* removerLista(Lista *lista) {
    Nodo *aux = lista->primeiro;
    while (aux != NULL) {
        Nodo *aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(lista);
    return NULL;
}

void liberarLista(Lista *lista) {
    Nodo *nodoAtual = lista->primeiro;
    while (nodoAtual != NULL) {
        Nodo *proximo = nodoAtual->prox;
        free(nodoAtual);
        nodoAtual = proximo;
    }
    free(lista);
}

NodoVertical* criarNodoVertical(Nodo* pasta) {
    NodoVertical* novo = (NodoVertical*) malloc(sizeof(NodoVertical));
    novo->pasta = pasta;
    novo->lista = criarLista();
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

NodoVertical* inserirNodoVertical(NodoVertical* nodoVertical, Nodo* pasta) {
    NodoVertical* novo = criarNodoVertical(pasta);
    NodoVertical* aux = nodoVertical;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = novo;
    novo->ant = aux;
    return novo;
}

NodoVertical* deletarNodoVertical(NodoVertical* nodoVertical) {
    NodoVertical* aux = nodoVertical->ant;
    if (aux != NULL) {
        aux->prox = nodoVertical->prox;
    }
    if (nodoVertical->prox != NULL) {
        nodoVertical->prox->ant = aux;
    }
    free(nodoVertical);
    return aux;
}

NodoVertical* buscarNodoVertical(NodoVertical* nodoVertical, Nodo* pasta) {
    NodoVertical* aux = nodoVertical;
    while (aux != NULL) {
        if (aux->pasta == pasta) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

NodoVertical* liberarNodoVertical(NodoVertical* nodoVertical) {
    liberarNodo(nodoVertical->pasta);
    liberarLista(nodoVertical->lista);
    NodoVertical* aux = nodoVertical;
    while (aux != NULL) {
        NodoVertical* aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    return NULL;
}

void listarNodosVerticais(NodoVertical* nodoVertical) {
    NodoVertical* aux = nodoVertical;
    while (aux != NULL) {
        printf("%s\n", aux->pasta->nome);
        listarNodos(aux->lista->primeiro);
        aux = aux->prox;
    }
}

void mostrarCaminho(Nodo* nodo) {
    printf("->%s\n", nodo->nome);
}

int main(){
    char str[14],cmd[3], par[11];
    Nodo *raiz = criarNodo("raizls", PASTA);
    NodoVertical *nodoVertical = criarNodoVertical(raiz);
    nodoVertical->lista = criarLista();
    NodoVertical *atual = nodoVertical;
    do{
        mostrarCaminho(raiz);
        fflush(stdin);
        gets(str);
        copiarStr(cmd, str, 0, 2);
        copiarStr(par, str, 3, 13);
        printf("str: %s\ncmd: %s\npar: %s\n\n", str, cmd, par);
        if (strcmp(cmd, "ma")== 0) {
            inserirNodoNaLista(atual->lista, par, ARQUIVO);
        } else if (strcmp(cmd, "mp")== 0) {
            inserirNodoNaLista(atual->lista, par, PASTA);
        } else if (strcmp(cmd, "ls") == 0) {
            listarNodos(atual->lista->primeiro);
        } else if (strcmp(cmd, "cd")== 0) {
            Nodo* nodo = buscarNodo(atual->lista->primeiro, par);
            if (nodo != NULL) {
                atual = inserirNodoVertical(atual, nodo);
            } else {
                printf("Nodo nao encontrado\n");
            }
        }
        printf("%s", atual->pasta->nome);    
        /*
        Nodo* nodo = raiz;
        nodo = inserirNodo(nodo, "pasta1", 0);
        nodo = inserirNodo(nodo, "pasta2", 0);
        nodo = inserirNodo(nodo, "pasta3", 0);
        nodo = deletarNodo(nodo);
        printf("nodo: %s\n",nodo->nome);
        printf("raiz: %s\n",raiz->nome);
        */
    } while(strcmp(cmd,"ex")!= 0);
    liberarNodoVertical(nodoVertical);
    return 0;
}

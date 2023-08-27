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

typedef struct listaVertical {
    Nodo *atual;
    Nodo *pai;
    Nodo *filho;
} ListaVertical;



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

ListaVertical* criarListaVertical(Nodo* nodo){
    ListaVertical *lista = (ListaVertical*) malloc(sizeof(ListaVertical));
    lista->atual = nodo;
    lista->pai = NULL;
    lista->filho = NULL;
    return lista;
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

void mostrarCaminho(Nodo* nodo) {
    printf("->%s\n", nodo->nome);
}

int main(){
    char str[14],cmd[3], par[11];
    Nodo *raiz = criarNodo("", PASTA);
    ListaVertical *listaVertical = criarListaVertical(raiz);
    Lista* lista = criarLista();
    do{
        mostrarCaminho(raiz);
        fflush(stdin);
        gets(str);
        copiarStr(cmd, str, 0, 2);
        copiarStr(par, str, 3, 13);
        printf("str: %s\ncmd: %s\npar: %s\n\n", str, cmd, par);
        if (strcmp(cmd, "ma")== 0) {
            inserirNodoNaLista(lista, par, ARQUIVO);
        } else if (strcmp(cmd, "mp")== 0) {
            inserirNodoNaLista(lista, par, PASTA);
        } else if (strcmp(cmd, "ls") == 0) {
            listarNodos(lista->primeiro);
        }
            
        /*
        Nodo* nodo = raiz;
        nodo = inserirNodo(nodo, "pasta1", 0);
        nodo = inserirNodo(nodo, "pasta2", 0);
        nodo = inserirNodo(nodo, "pasta3", 0);
        nodo = deletarNodo(nodo);
        printf("nodo: %s\n",nodo->nome);
        printf("raiz: %s\n",raiz->nome);
        */
    } while(strcmp(cmd,"ex")!=0);
    liberarLista(lista);
    return 0;
}

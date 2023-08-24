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

typedef struct listaVertical {
    Nodo *atual;
    Nodo *pai;
    Nodo *filho;
} ListaVertical;

typedef struct lista {
    Nodo *atual;
    Nodo *prox;
    Nodo *ant;
} Lista;

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

Nodo* inserirNodo(Nodo *pai, char nome[], int tipo){
    Nodo *novo = criarNodo(nome, tipo);
    novo->ant = pai;
    if(pai->prox == NULL){
        pai->prox = novo;
    }else{
        Nodo *aux = pai->prox;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->ant = aux;
    }
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
        printf("%s\n",aux->nome);
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
    lista->atual = NULL;
    lista->prox = NULL;
    lista->ant = NULL;
    return lista;
}

Lista* removerLista(Lista *lista){
    Nodo *aux = lista->atual;
    while(aux != NULL){
        aux = aux->prox;
        free(aux->ant);
    }
    free(lista);
    return NULL;
}

int main(){
    char str[14],cmd[3], par[11];
    Nodo* raiz = criarNodo("", PASTA);
    ListaVertical* listaVertical = criarListaVertical(raiz);
    do{
        fflush(stdin);
        gets(str);
        copiarStr(cmd, str, 0, 2);
        copiarStr(par, str, 3, 13);
        printf("str: %s\ncmd: %s\npar: %s\n\n", str, cmd, par);
        if (strcmp(cmd,"ma")==0) {
            Nodo* arquivo = criarNodo(par, ARQUIVO);
            listaVertical->filho = inserirNodo(arquivo, par, ARQUIVO);
            printf("arquivo: %s\n", arquivo->nome);
            printf("listaVertical->filho: %s\n", listaVertical->filho->nome);
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
    return 0;
}

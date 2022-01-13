#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct estr {
    int chave;
    struct estr* esq;
    struct estr* dir;
}NO;

typedef struct elemento{
    NO* reg;
    struct elemento* prox;
} ELEMENTO;


typedef struct {
    ELEMENTO* inicio;
    ELEMENTO* fim;
} Fila;


bool inserir(NO* *raiz, int ch){
    if(*raiz == NULL){
        NO* novo = (NO*)malloc(sizeof(NO));
        novo->chave = ch;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return true;
    }else{
        if((*raiz)->chave >= ch)
            return inserir(&(*raiz)->esq, ch);
        else return inserir(&(*raiz)->dir, ch);
    }
}

void inicializarFila(Fila* f) {
 f->inicio = NULL;
 f->fim = NULL;
}

void entrar(NO* no, Fila* f){
    ELEMENTO* novo = (ELEMENTO*)malloc(sizeof(ELEMENTO));
    novo->reg = no;
    novo->prox = NULL;
    if(f->fim) f->fim->prox = novo;
    else f->inicio = novo;
    f->fim = novo;
}


NO* sair(Fila* f){
    ELEMENTO* aux;
    NO* ch;
    if(!f->inicio) return NULL;
    ch = f->inicio->reg;
    aux = f->inicio;
    f->inicio = f->inicio->prox;
    free(aux);
    if(!f->inicio) f->fim = NULL;
    return(ch);
}

int somarNivelMaisExtenso(NO* raiz) {
    int soma = 0;
    int auxsoma = 0;
    int nos = 0;
    int auxnos = 0;
    NO* pai = NULL;
    NO* auxPai = NULL;
    NO* root = raiz;

    Fila filaPai;
    inicializarFila(&filaPai);

    Fila filaFilho;
    inicializarFila(&filaFilho);

    entrar(root, &filaPai);

    while((root) || (filaPai.inicio)){

        while(filaPai.inicio){
            auxPai = sair(&filaPai);
            if (auxPai->esq){
                entrar(auxPai->esq, &filaFilho);
                auxnos += 1;
                auxsoma += auxPai->esq->chave;
            }
            if(auxPai->dir){
                entrar(auxPai->dir, &filaFilho);
                auxnos += 1;
                auxsoma += auxPai->dir->chave;
            }
        }

        if(auxnos > nos){
            nos = auxnos;
            soma = auxsoma;
        }

        while(auxnos>0){
            pai = sair(&filaFilho);
            entrar(pai, &filaPai);
            auxnos --;
        }

        auxnos = 0;
        auxsoma = 0;

        root = NULL;
    }
    return soma;
}

void exibirEmOrdem(NO *raiz){
    if(raiz == NULL) return;
    exibirEmOrdem(raiz->esq);
    printf("%i ", raiz->chave);
    exibirEmOrdem(raiz->dir);
}



int main()
{

    NO* root = NULL;
    inserir(&root, 8);
    inserir(&root, 3);
    inserir(&root, 10);
    inserir(&root, 1);
    inserir(&root, 6);
    inserir(&root, 14);
    inserir(&root, 4);
    inserir(&root, 7);
    inserir(&root, 13);

    int res = somarNivelMaisExtenso(root);

    printf(" soma %d", res);

    return 0;
}

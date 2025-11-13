#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5

typedef struct {
    char nome;
    int id;
} Peca;

typedef struct {
    Peca pecas[TAM];
    int inicio, fim, qtd;
} Fila;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
}

int filaVazia(Fila *f) {
    return f->qtd == 0;
}

int filaCheia(Fila *f) {
    return f->qtd == TAM;
}

Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

void enfileirar(Fila *f, Peca p) {
    if (filaCheia(f)) return;
    f->pecas[f->fim] = p;
    f->fim = (f->fim + 1) % TAM;
    f->qtd++;
}

void desenfileirar(Fila *f) {
    if (filaVazia(f)) return;
    f->inicio = (f->inicio + 1) % TAM;
    f->qtd--;
}

void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Fila de peças:\n");
    int i, pos = f->inicio;
    for (i = 0; i < f->qtd; i++) {
        printf("[%c %d] ", f->pecas[pos].nome, f->pecas[pos].id);
        pos = (pos + 1) % TAM;
    }
    printf("\n");
}

int main() {
    Fila fila;
    inicializarFila(&fila);
    int opcao, id = 0;
    srand(time(NULL));

    for (int i = 0; i < TAM; i++) enfileirar(&fila, gerarPeca(id++));

    do {
        exibirFila(&fila);
        printf("\n1 - Jogar peça\n2 - Inserir nova peça\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) desenfileirar(&fila);
        else if (opcao == 2 && !filaCheia(&fila)) enfileirar(&fila, gerarPeca(id++));
        else if (opcao == 2) printf("Fila cheia!\n");

    } while (opcao != 0);

    return 0;
}

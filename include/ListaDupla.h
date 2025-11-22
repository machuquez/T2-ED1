#ifndef LISTA_DUPLA_H
#define LISTA_DUPLA_H

#define FALSO      0
#define VERDADEIRO 1
#define OK         1
#define ERRO       0


struct elemento {
    void *dado;                    //  Ponteiro genérico
    struct elemento *ant;          // Ponteiro para anterior
    struct elemento *prox;       // Ponteiro para próximo
};

typedef struct elemento Elem;
typedef struct elemento* Lista;

// Estrutura da lista dupla (com li,lf e lc)
struct lista_dupla {
    Elem* li;  // Ponteiro para início
    Elem* lf;  // Ponteiro para fim
    Elem* lc;  //Ponteiro para o cursor
    int tamanho;
};

typedef struct lista_dupla ListaDupla;

// Protótipos GENÉRICOS
ListaDupla* cria_lista_dupla();
void libera_lista_dupla(ListaDupla* ld);
int insere_lista_dupla_final(ListaDupla* ld, void *dado, unsigned int tamanho_dado);
int insere_lista_dupla_inicio(ListaDupla* ld, void *dado, unsigned int tamanho_dado);
int insere_lista_dupla_ordenada(ListaDupla* ld, void *dado, unsigned int tamanho_dado, int (*compara)(void*, void*));
int remove_lista_dupla_inicio(ListaDupla* ld);
int remove_lista_dupla_final(ListaDupla* ld);
int remove_lista_dupla_especifico(ListaDupla* ld, void* chave, int (*compara)(void*, void*));
int tamanho_lista_dupla(ListaDupla* ld);
int lista_dupla_vazia(ListaDupla* ld);
void* busca_lista_dupla(ListaDupla* ld, void* chave, int (*compara)(void*, void*));
void imprime_lista_dupla(ListaDupla* ld, void (*imprime)(void*));
void imprime_lista_dupla_inverso(ListaDupla* ld, void (*imprime)(void*));
void insere_lista_dupla_ACursor(ListaDupla *ld,void *dado, unsigned int tamanho_dado);
void insere_lista_dupla_DCursor(ListaDupla *ld,void *dado, unsigned int tamanho_dado);
void remove_atual(ListaDupla* ld);
void cursorfinal(ListaDupla* ld);
void cursorcomeco(ListaDupla* ld);
void antNo(ListaDupla* ld);
void proxNo(ListaDupla* ld);

#endif

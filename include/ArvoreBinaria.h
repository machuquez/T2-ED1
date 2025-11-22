// Dentro de ./include/ArvoreBinaria.h

#ifndef ARVORE_BINARIA_H // <--- GUARDA CORRETA para a Árvore
#define ARVORE_BINARIA_H

// Incluir o cabeçalho da Lista Dupla para que os tipos Elem e ListaDupla sejam definidos.
#include "ListaDupla.h" 

// Definição da estrutura do Nó da Árvore
struct EstruturaArvore{
    long int CPF;
    // Referência correta à struct interna para a recursão
    struct EstruturaArvore *Esquerda; 
    struct EstruturaArvore *Direita;  
    // Agora 'struct Elem' é conhecido
    struct Elem *NoListaDupla; 
};
typedef struct EstruturaArvore NoArvore;

// Definição da estrutura do Gerenciador da Árvore
struct GerenciadorarvoreBinaria{
    NoArvore *Raiz;
    int quantNos;
    int tamanho;    
};
typedef struct GerenciadorarvoreBinaria ArvoreBinaria;

// Protótipos das funções da Árvore
ArvoreBinaria *criaArvoreBinaria(void);
void AdicionaElementoArvoreBinaira(long int CPFNOVO, ArvoreBinaria *Arvore, Elem *NoInserido);
void liberar_no(NoArvore *no);
void liberaArvoreBinaria(ArvoreBinaria *Arvore);

#endif // ARVORE_BINARIA_H

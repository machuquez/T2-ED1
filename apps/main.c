#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ArvoreBinaria.h"
#include "ListaDupla.h"


typedef struct {
    char CPF[10];      // 9 dígitos
    char DV[3];        // 2 dígitos
    char DataNasc[11]; // DD/MM/AAAA
    char Nome[51];     //50 char
} Registro;


long int converte_string_para_long(char *s, int tamanho) {
    char temp[10];
    strncpy(temp, s, tamanho);
    temp[tamanho] = '\0';
    return atol(temp);
}

void insere_registro_completo(ListaDupla *ld, ArvoreBinaria *ab, Registro *reg) {
    int sucesso = insere_lista_dupla_inicio(ld, reg, sizeof(Registro));
    
    if (sucesso == OK) {
        Elem *no_lde_inserido = ld->li; 
        
        long int cpf_chave = converte_string_para_long(reg->CPF, 9);
        AdicionaElementoArvoreBinaira(cpf_chave, ab, no_lde_inserido);
    } else {
        printf("Erro de memória ao inserir na LDE.\n");
    }
}


NoArvore* busca_extremo(NoArvore *raiz, int buscar_minimo) {
    if (raiz == NULL) return NULL;
    
    NoArvore *atual = raiz;
    if (buscar_minimo) { // Busca o menor (extrema esquerda)
        while (atual->Esquerda != NULL) {
            atual = atual->Esquerda;
        }
    } else { // Busca o maior (extrema direita)
        while (atual->Direita != NULL) {
            atual = atual->Direita;
        }
    }
    return atual;
}

// Função imprime_saida_terminal
void imprime_saida_terminal(ArvoreBinaria *ab) {
    if (ab == NULL || ab->Raiz == NULL) {
        printf("0\n0\n(Vazio)\n(Vazio)\n");
        return;
    }
    
    printf("%d\n", ab->quantNos);
    
    printf("%d\n", ab->tamanho);
    
    NoArvore *primeiro_no_ab = busca_extremo(ab->Raiz, VERDADEIRO);
    if (primeiro_no_ab != NULL && primeiro_no_ab->NoListaDupla != NULL) {
        Registro *reg = (Registro*)primeiro_no_ab->NoListaDupla->dado;
        printf("%s-%s %s %s\n", reg->CPF, reg->DV, reg->DataNasc, reg->Nome);
    } else {
        printf("(Erro ao buscar primeiro)\n");
    }

    NoArvore *ultimo_no_ab = busca_extremo(ab->Raiz, FALSO);
    if (ultimo_no_ab != NULL && ultimo_no_ab->NoListaDupla != NULL) {
        Registro *reg = (Registro*)ultimo_no_ab->NoListaDupla->dado;
        printf("%s-%s %s %s\n", reg->CPF, reg->DV, reg->DataNasc, reg->Nome);
    } else {
        printf("(Erro ao buscar último)\n");
    }
}

void imprime_lista_para_arquivo(ListaDupla *ld) {
    FILE *arq = fopen("dados1.txt", "w");
    if (arq == NULL) {
        perror("Erro ao criar dados1.txt");
        return;
    }
    
    Elem *no = ld->li;
    while (no != NULL) {
        Registro *reg = (Registro*)no->dado;
        fprintf(arq, "%s-%s %s %s\n", reg->CPF, reg->DV, reg->DataNasc, reg->Nome);
        no = no->prox;
    }
    fclose(arq);
}

void imprime_ab_inorder_para_arquivo(NoArvore *no, FILE *arq) {
    if (no == NULL) return;
    
    imprime_ab_inorder_para_arquivo(no->Esquerda, arq);
    
    if (no->NoListaDupla != NULL) {
        Registro *reg = (Registro*)no->NoListaDupla->dado;
        // Imprime apenas os 9 dígitos do CPF
        fprintf(arq, "%s\n", reg->CPF); 
    }
    
    imprime_ab_inorder_para_arquivo(no->Direita, arq);
}

// Função processa_arquivo
void processa_arquivo(ListaDupla *ld, ArvoreBinaria *ab) {
    FILE *arq = fopen("basedados.csv", "r");
    if (arq == NULL) {
        arq = fopen("basedados.txt", "r");
        if (arq == NULL) {
            perror("Erro: Arquivo 'basedados.csv' ou 'basedados.txt' nao encontrado");
            return;
        }
        printf("Aviso: Usando 'basedados.txt'. Será aplicada a penalidade de -0.3 pts.\n");
    }

    char linha[256];
    char *buffer;
    
    // Ignora a primeira linha (cabeçalho), se houver
    if (fgets(linha, sizeof(linha), arq) == NULL) return; 

    while (fgets(linha, sizeof(linha), arq) != NULL) {
        linha[strcspn(linha, "\n")] = 0;
        if (strcmp(linha, "-1") == 0) break;
        Registro novo_reg;
        buffer = strtok(linha, ";, \t"); 
        if (buffer) strncpy(novo_reg.CPF, buffer, 9); novo_reg.CPF[9] = '\0';
        buffer = strtok(NULL, ";, \t"); 
        if (tbuffer) strncpy(novo_reg.DV, buffer, 2); novo_reg.DV[2] = '\0';
        buffer = strtok(NULL, ";, \t"); 
        if (buffer) strncpy(novo_reg.DataNasc, buffer, 10); novo_reg.DataNasc[10] = '\0';
        buffer = strtok(NULL, "\n");
        if (buffer) {
            while(*buffer == ' ') buffer++;
            strncpy(novo_reg.Nome, buffer, 50);
            novo_reg.Nome[50] = '\0';
        } else {
            novo_reg.Nome[0] = '\0';
        }
        
        insere_registro_completo(ld, ab, &novo_reg);
    }
    
    fclose(arq);
}


int main() {
    int opcao;
    
    printf("Digite 1 para Execucao Padrao ou 2 para Execucao com 'cat':\n");
    if (scanf("%d", &opcao) != 1 || (opcao != 1 && opcao != 2)) {
        printf("Opcao invalida. Encerrando.\n");
        return 1;
    }
    
    ArvoreBinaria *ab = criaArvoreBinaria();
    ListaDupla *ld = cria_lista_dupla();
    
    if (ab == NULL || ld == NULL) {
        printf("Erro fatal de alocacao de memoria.\n");
        return 1;
    }
    
    processa_arquivo(ld, ab);
    
    printf("\n--- Saida no Terminal ---\n");
    imprime_saida_terminal(ab);
    printf("-------------------------\n");
    
    imprime_lista_para_arquivo(ld);
    
    FILE *arq2 = fopen("dados2.txt", "w");
    if (arq2 != NULL) {
        imprime_ab_inorder_para_arquivo(ab->Raiz, arq2);
        fclose(arq2);
    } else {
        perror("Erro ao criar dados2.txt");
    }
    
    if (opcao == 2) {
        printf("\n--- Execucao Adicional (Opcao 2) ---\n");
        system("cat dados1.txt");
        system("cat dados2.txt");
        printf("--------------------------------------\n");
    }
    
    liberaArvoreBinaria(ab);
    libera_lista_dupla(ld);
    
    return 0;
}

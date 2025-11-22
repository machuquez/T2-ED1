#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDupla.h"


ListaDupla* cria_lista_dupla() {
    ListaDupla* ld = (ListaDupla*) malloc(sizeof(ListaDupla));
    if(ld != NULL) {
        ld->li = NULL;
        ld->lf = NULL;
        ld->lc = NULL;
        ld->tamanho = 0;
    }
    return ld;
}


void libera_lista_dupla(ListaDupla* ld) {
    if(ld == NULL) return;

    Elem* no = ld->li;
    while(no != NULL) {
        Elem* proximo = no->prox;
        free(no->dado);
        free(no);
        no = proximo;
    }
    free(ld);
}


int insere_lista_dupla_final(ListaDupla* ld, void *dado, unsigned int tamanho_dado) {
    if(ld == NULL || dado == NULL) return ERRO;

    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return ERRO;

    no->dado = malloc(tamanho_dado);
    if(no->dado == NULL) {
        free(no);
        return ERRO;
    }
    memcpy(no->dado, dado, tamanho_dado);

    no->prox = NULL;
    no->ant = ld->lf;  // Anterior aponta para o antigo último

    if(ld->lf == NULL) {
        // Lista vazia
        ld->li = no;
        ld->lf = no;
        ld->lc = no;
    } else {
        // Lista não vazia
        ld->lf->prox = no;
        ld->lf = no;
    }

    ld->tamanho++;
    return OK;
}
void remove_atual(ListaDupla* ld){
	if(ld==NULL)return;
	Elem* no = ld->lc;
	if(no==NULL){
	//printf("Erro, ainda nao possui cursor");
	return;
	}
	//O que tenho que fazer, finfir que esse no nunca existiu e dar free nele como o ponteiro vai para o anterior(o cursos ta nesse no)
	//Trata caso esteja querendo remover o unico item da lista ou no extremos
	if(ld->li == ld->lf) {
        ld->li = NULL;
        ld->lf = NULL;
        ld->lc = NULL;
    	}
	else if(no->ant==NULL){
	no->prox->ant=NULL;	
	ld->li=no->prox;
	ld->lc=no->prox;
	}
	else if(no->prox==NULL){
	no->ant->prox=NULL;	
	ld->lf=no->ant;
	ld->lc=no->ant;
	}
	else{
	//1 passa vai para o prox e muda o anterior dele para o anterior do lc
	no->prox->ant=no->ant;
	//2 passo vai para o ant e muda o prox dele para o proximo do lc
	no->ant->prox=no->prox;
	ld->lc=no->prox;
	}
	//3 passo da free na memoria alocada e move o cursor para o anteior
	free(no->dado);
    	free(no);
    	ld->tamanho--;
    	return;
	//4 passo FIm
}
void cursorcomeco(ListaDupla* ld){
	if(ld==NULL)return;
	if(ld->li==NULL)return;
	ld->lc=ld->li;
	return;
}
void cursorfinal(ListaDupla* ld){
	if(ld==NULL)return;
	if(ld->lf==NULL)return;
	ld->lc=ld->lf;
	return;
}

void proxNo(ListaDupla* ld){
	if(ld==NULL)return;
	if(ld->li==NULL)return;
	if(ld->lc==NULL)return;
	if(ld->lc->prox!=NULL){
	ld->lc=ld->lc->prox;
	return;
	}
	//else printf("Erro, nao faz sentido");
}

void antNo(ListaDupla* ld){
	if(ld==NULL)return;
	if(ld->li==NULL)return;
	if(ld->lc==NULL)return;
	if(ld->lc->ant!=NULL){
	ld->lc=ld->lc->ant;
	return;
	}
	//else printf("Erro, nao faz senti");
}

void insere_lista_dupla_ACursor(ListaDupla *ld,void *dado, unsigned int tamanho_dado){
	if(ld == NULL || dado== NULL)return;
	
	Elem* no =(Elem*) malloc(sizeof(Elem));
	
	if(no ==NULL)return;
	
	no->dado = malloc(tamanho_dado);
	if(no->dado==NULL){
		free(no);
		return;
	}
	//Copia os dados da struct
	 memcpy(no->dado, dado, tamanho_dado);

	//1 caso-> Lista Vazia
	if(ld->li==NULL){
		no->prox=NULL;
		no->ant=NULL;
		ld->li=no;
		ld->lf=no;
		ld->lc=no;
		}
	//2 caso-> Lista nao vaiza
	else{
		//Inserir antes do cursor ,ajustando os ponteiros do proprio no
		no->prox=ld->lc;
		no->ant=ld->lc->ant;

		//Ajustar os outros ponteiros-> Verificar se ele nao [e o primeiro elemento
		if(ld->lc->ant!=NULL){
		ld->lc->ant->prox=no;		
		}
		else{
		ld->li=no;
		}

		ld->lc->ant = no;
        	ld->lc = no;
	}


    ld->tamanho++;
    return;
}

void insere_lista_dupla_DCursor(ListaDupla *ld,void *dado, unsigned int tamanho_dado){
	if(ld == NULL || dado== NULL)return;
	
	Elem* no =(Elem*) malloc(sizeof(Elem));
	
	if(no ==NULL)return;
	
	no->dado = malloc(tamanho_dado);
	if(no->dado==NULL){
		free(no);
		return;
	}
	//Copia os dados da struct
	 memcpy(no->dado, dado, tamanho_dado);

	//1 caso-> Lista Vazia
	if(ld->li==NULL){
		no->prox=NULL;
		no->ant=NULL;
		ld->li=no;
		ld->lf=no;
		ld->lc=no;
		}
	//2 caso-> Lista nao vaiza
	else{
		//Inserir antes do cursor ,ajustando os ponteiros do proprio no
		no->ant=ld->lc;
		no->prox=ld->lc->prox;

		//Ajustar os outros ponteiros-> Verificar se ele nao o ultimo elemento da lista
		if(ld->lc->prox!=NULL){
		ld->lc->prox->ant=no;		
		}
		else{
		ld->li=no;
		}

		ld->lc->prox = no;
        	ld->lc = no;
	}


    ld->tamanho++;
    return;

}

int insere_lista_dupla_inicio(ListaDupla* ld, void *dado, unsigned int tamanho_dado) {
    if(ld == NULL || dado == NULL) return ERRO;

    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return ERRO;

    no->dado = malloc(tamanho_dado);
    if(no->dado == NULL) {
        free(no);
        return ERRO;
    }
    memcpy(no->dado, dado, tamanho_dado);

    no->ant = NULL;
    no->prox = ld->li;

    if(ld->li == NULL) {
        // Lista vazia
        ld->li = no;
        ld->lc = no;
        ld->lf = no;
    } else {
        // Lista não vazia
        ld->li->ant = no;
        ld->li = no;
    }

    ld->tamanho++;
    return OK;
}






int tamanho_lista_dupla(ListaDupla* ld) {
    if(ld == NULL) return 0;
    return ld->tamanho;
}


int lista_dupla_vazia(ListaDupla* ld) {
    if(ld == NULL) return 1;
    return (ld->li == NULL);
}








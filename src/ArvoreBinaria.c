#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ArvoreBinaria.h"
#include "ListaDupla.h" 

//Implementacao de uma arvore binaria com lista
//Cria ArvoreBinaria
ArvoreBinaria *criaArvoreBinaria(){
	
//Alocar os Espaco para uma arvore binaria no caso a estrututa
	ArvoreBinaria *ArvoreCriada;
	ArvoreCriada=(ArvoreBinaria *)malloc(sizeof(ArvoreBinaria));
	if(ArvoreCriada==NULL){
		printf("Erro ao criar uma Arvore Binaria-memoria");
		return NULL;
	}
	ArvoreCriada->Raiz=NULL;
	ArvoreCriada->quantNos=0;
	ArvoreCriada->tamanho=0;
return(ArvoreCriada);
}



//Adiciona um novo elemento da ArvoreBinaria

void AdicionaElementoArvoreBinaira(long int CPFNOVO,ArvoreBinaria *Arvore, Elem *NoInserido){
	if(Arvore==NULL){
		printf("Impossivel adicionar elemento, arvore nao existe");
		return;
	}
	NoArvore *NovoNoArvore=malloc(sizeof(NoArvore));
	if(NovoNoArvore==NULL){
		printf("Nao foi possivel criar um novo no");
		return;
	}
	NovoNoArvore->CPF=CPFNOVO;
	NovoNoArvore->Esquerda=NULL;
	NovoNoArvore->Direita=NULL;
	NovoNoArvore->NoListaDupla=NoInserido;
	//Caso seja o primeiro elemento
	if(Arvore->Raiz==NULL){
		Arvore->Raiz=NovoNoArvore;
		Arvore->quantNos=1;
		Arvore->tamanho=1;//Altura
	}
	
	NoArvore *Atual=Arvore->Raiz;
	NoArvore *Anterior=NULL;
	int encontrou=0; //Caso seja um elemento de meio ou no folha da arvore
	int altura_atual = 1;//Do caminho
	while(Atual!=NULL){
		Anterior=Atual;
		//Tratamento caso o CPF seja duplicado
		if(Atual->CPF==CPFNOVO){
		printf("CPF ja adicionado na lista(CPF duplicado)");
		free(NovoNoArvore);
		return;
		}
		if(CPFNOVO<Atual->CPF){
			Atual=Atual->Esquerda;
		}
		else{
			Atual=Atual->Direita;
		}
		altura_atual++;
		}
	if(CPFNOVO<Anterior->CPF){
		Anterior->Esquerda=NovoNoArvore;
	}
	else{
		Anterior->Direita=NovoNoArvore;
	}
	Arvore->quantNos++;
	if (altura_atual > Arvore->tamanho) {
        Arvore->tamanho = altura_atual;
    }
    
}

//Libera ArvoreBinaria
void liberar_no(NoArvore *no) {
    if (no == NULL) {
        return;
    }
    
    liberar_no(no->Esquerda);
    
    liberar_no(no->Direita);
    
    free(no);
}

void liberaArvoreBinaria(ArvoreBinaria *Arvore) {
    if (Arvore == NULL) {
        return;
    }
    

    liberar_no(Arvore->Raiz);
    

    Arvore->Raiz = NULL;
    Arvore->quantNos = 0;
    Arvore->tamanho = 0;
    

    free(Arvore);
}




















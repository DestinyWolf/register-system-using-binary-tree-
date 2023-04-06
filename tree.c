#include <stdlib.h>
#include <stdio.h>
#include "tree.h"



tree * search(tree * root, int id){
	if (root->data.cpf == id){
		return root;
	}
	else if(root->data.cpf < id)
		return search(root->r, id);
	else
		return search(root->l, id);
}


int insert(tree ** root, typedata data){
	tree*leaf = (tree*) malloc(sizeof(tree));
	tree*parent = *root;
	
	leaf->l = NULL;//aterro 
	leaf->r = NULL;//aterro o lado esquerdo da folha
	
	leaf->data = data;
	leaf->bal = 0;
	
	if(*root){ // se a raiz não for nula 
		while(parent->r != NULL || parent->l != NULL){ //enquanto não chegar em uma folha o loop repete
			if (parent->data.cpf > data.cpf) 
				parent = parent->l;
			else
				parent = parent->r;
		}
		
		if (parent->data.cpf > data.cpf){
			parent->l = leaf;
			parent->bal --;
		}
		else{
			parent->r = leaf;
		}

		leaf->parent = parent;
	}
	else{
		*root = leaf;
		leaf->parent = NULL;
	}
}

int remove(tree **root, int id)
{
    tree* parent = search((*root), id); //usa a função search pra encontrar o galho/folha que sera removido

	if(parent){ // verifico se o galho que será removido existe
		if(parent->l == NULL && parent->r == NULL){ //caso ambos os lados sejam nulos

			if(parent->parent->data.cpf > parent->data.cpf){ //verifico se é filho esquerdo do pai
				parent->parent->l = NULL;// se for atribuu nulo ao filho esquerdo do pai
				parent->parent->bal ++; //removo do fator de balancento 1
			}
			else{//caso contrario
				parent->parent->r = NULL; //atribuo nulo ao filho direito do pai
				parent->parent->bal --; //removo um do fator de balanceamento
			}
		}

		else if(parent->l != NULL && parent->r == NULL){ //caso ele tenha um filho esquerdo
			if(parent->parent->data.cpf > parent->data.cpf){ // verifico se ele é o filho esquerdo do pai 

				parent->parent->l = parent->l; //atribuo ao filho esquerdo do avo o filho esquerdo do pai
				//free
			}
			else{ // caso seja o filho direito
				parent->parent->r = parent->l; //atribuo ao filho direito do avo o filho esquerdo do pai
				//free
			}
		}

		else if(parent->l == NULL && parent->r != NULL){ //caso ele tenha um filho direito
			if(parent->parent->data.cpf > parent->data.cpf){ // verifico se ele é o filho esquerdo do pai 

				parent->parent->l = parent->r; //atribuo ao filho esquerdo do avo o filho esquerdo do pai
				//free
			}
			else{ // caso seja o filho direito
				parent->parent->r = parent->r; //atribuo ao filho direito do avo o filho esquerdo do pai
				//free
			}
		}

		else if(parent->l != NULL && parent->r != NULL){} //caso ele tenha dois filhos
	}

	
	
	return 0;
}

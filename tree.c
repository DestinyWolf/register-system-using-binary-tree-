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
	
	leaf->l = NULL;//aterro o lado esquerdo da folha
	leaf->r = NULL;//aterro o lado direito da folha
	
	leaf->data = data;//faço a copia dos dados para a folha
	leaf->bal = 0;//seto o fator de balanceamento para zero
	
	if(*root){ // se a raiz não for nula 
		while(parent->r != NULL || parent->l != NULL){ //enquanto não chegar em uma folha o loop repete
			if (parent->data.cpf > data.cpf) //verifico se é uma folha direita ou esquerda
				parent = parent->l;//se for esquerda faço o pai receber o seu filho esquerdo
			else//caso contrario
				parent = parent->r;//faço o pai receber seu filho direito
		}
		
		if (parent->data.cpf > data.cpf){// se o cpf do pai for maior do que o da folha
			parent->l = leaf; //atribuo ele ao lado esquerdo
			balancing_factor(parent, '-');//chamo a função de balanceamento e passo a informação de que é um filho esquerdo
		}
		else{//caso contrario
			parent->r = leaf;//atribuo ao lado direito
			balancing_factor(parent, '+');//chamo a função de balanceamento para o lado e informo que é um filho direito
		}

		leaf->parent = parent;//informo a folha quem é o pai 
	}
	else{//se a raiz for nula
		*root = leaf;//faço a raiz ser a folha
		leaf->parent = NULL;//informo que ela é a raiz, ou seja, não tem pai
	}
}

/*
função reponsavel por realizar a remoção de galhos e folhas 
*/

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

		//caso ele tenha dois filhos
		else if(parent->l != NULL && parent->r != NULL){
				tree*aux; // variavel auxiliar para movimentação

			if(parent->parent->data.cpf > parent->data.cpf){ // verifico se ele é o filho esquerdo do pai 
				
				aux = parent->r; // atribuo a aux o filho direito do pai
				parent->parent->l = parent->r; // atribuo ao filho esquerdo do avo o filho direito do pai

				while (aux->l != NULL ) // enquanto não encontrar um filho esquerdo que seja nulo, ou seja, que possa ser inserida uma folha
				{
					aux = aux->l; // aux recebe o seu galho esquerdo 
				}

				aux->l = parent->l; //atribuo ao filho esquerdo de aux o filho esquerdo do pai
				

				
			}
			else{ // caso seja o filho direito
				aux =parent->l; // atribuo a aux o filho esquerdo do parente
				parent->parent->r = parent->l;//atribuo ao lado direito do avo o filho esquerdo do pai 
				
				while(aux->r != NULL){ //enquanto não achar um filho direito que seja nulo, ou seja, onde dê pra inserir uma folha
					aux = aux->r; // atribuo aux o proximo filho direito
				}

				aux->r = parent->r; // atribuo ao filho direito do aux o filho direito do pai
			}

		}

		free(parent); // removo o pai 

		return true;
	}
	else
		return false;
}

void balancing_factor(tree **root, char sign)
{
	int before_bal = (*root)->bal; //pega o fator de balancemento anterior

	switch (sign)//olha para o sinal de balancemento
	{
	case '-': //caso seja um filho esquerdo

		(*root)->bal--;//subtrai uma unidade do fator de balancemanto

		if(abs((*root)->bal) == 2){ // se o fator de balanceamento em modulo for igual a 2
			rotate(root);//faz a rotação
		}

		else if (abs( (*root)->bal) > abs(before_bal)) // se o fator de balanceamento atual for maior que o anterior em modulo
		{
			balancing_factor(&((*root)->parent), '-'); // chama a função de maneira recursiva e passa como sinal -, para subtrair uma unidade do balanceamento do pai
		}
		else if(abs( (*root)->bal) < abs(before_bal)){ // se for menor que o anterior
			balancing_factor(&((*root)->parent), '+'); //passa como sinal +, para adicionar uma unidade no fator de balanceamento do pai
		}
		break;

	case '+'://caso seja um filho direito
		(*root)->bal++;//adiciona uma unidade ao fator de balancemanto

		if(abs((*root)->bal) == 2){ // verifica se o fator de balanceamento é igual a 2 em modulo
			rotate(root);//caso seja, faz a rotação
		}

		else if (abs( (*root)->bal) > abs(before_bal) ) // se o fator de balanceamento atual for maior que o anterior
		{
			balancing_factor(&((*root)->parent), '+');//passa com o sinal de +, para adicionar uma unidade ao fator de balanceamento do pai
		}
		else if(abs( (*root)->bal) < abs(before_bal)){//caso seja menor
			balancing_factor(&((*root)->parent), '-'); //passa com menos, para subtrair uma unidade do fator de balanceamento 
		}
		break;
	}
}

void  rotate(tree **root)
{
	tree*aux = (*root)->parent;

	if((*root)->bal == -2 && (*root)->l->bal == -1){
		rotate_right(root);
		aux->l =  (*root)->parent;
		(*root)->parent->parent = aux;
	}

	else if((*root)->bal == +2 && (*root)->l->bal == +1){
		rotate_left(root);
		aux->r =  (*root)->parent;
		(*root)->parent->parent = aux;
	}
}

void rotate_left(tree **root)
{
	(*root)->r = *root;
	(*root)->parent = (*root)->r;
}

void rotate_right(tree **root)
{
	(*root)->l->r = *root;
	(*root)->parent = (*root)->l;
}

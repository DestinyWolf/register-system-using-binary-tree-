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
	
	leaf->data = data;//fa�o a copia dos dados para a folha
	leaf->bal = 0;//seto o fator de balanceamento para zero
	
	if(*root){ // se a raiz n�o for nula 
		while(parent->r != NULL || parent->l != NULL){ //enquanto n�o chegar em uma folha o loop repete
			if (parent->data.cpf > data.cpf) //verifico se � uma folha direita ou esquerda
				parent = parent->l;//se for esquerda fa�o o pai receber o seu filho esquerdo
			else//caso contrario
				parent = parent->r;//fa�o o pai receber seu filho direito
		}
		
		if (parent->data.cpf > data.cpf){// se o cpf do pai for maior do que o da folha
			parent->l = leaf; //atribuo ele ao lado esquerdo
			balancing_factor(parent, '-');//chamo a fun��o de balanceamento e passo a informa��o de que � um filho esquerdo
		}
		else{//caso contrario
			parent->r = leaf;//atribuo ao lado direito
			balancing_factor(parent, '+');//chamo a fun��o de balanceamento para o lado e informo que � um filho direito
		}

		leaf->parent = parent;//informo a folha quem � o pai 
	}
	else{//se a raiz for nula
		*root = leaf;//fa�o a raiz ser a folha
		leaf->parent = NULL;//informo que ela � a raiz, ou seja, n�o tem pai
	}
}

/*
fun��o reponsavel por realizar a remo��o de galhos e folhas 
*/

int remove(tree **root, int id)
{
    tree* parent = search((*root), id); //usa a fun��o search pra encontrar o galho/folha que sera removido

	if(parent){ // verifico se o galho que ser� removido existe
		if(parent->l == NULL && parent->r == NULL){ //caso ambos os lados sejam nulos

			if(parent->parent->data.cpf > parent->data.cpf){ //verifico se � filho esquerdo do pai
				parent->parent->l = NULL;// se for atribuu nulo ao filho esquerdo do pai
				parent->parent->bal ++; //removo do fator de balancento 1
			}
			else{//caso contrario
				parent->parent->r = NULL; //atribuo nulo ao filho direito do pai
				parent->parent->bal --; //removo um do fator de balanceamento
			}
		}

		else if(parent->l != NULL && parent->r == NULL){ //caso ele tenha um filho esquerdo
			if(parent->parent->data.cpf > parent->data.cpf){ // verifico se ele � o filho esquerdo do pai 

				parent->parent->l = parent->l; //atribuo ao filho esquerdo do avo o filho esquerdo do pai
				//free
			}
			else{ // caso seja o filho direito
				parent->parent->r = parent->l; //atribuo ao filho direito do avo o filho esquerdo do pai
				//free
			}
		}

		else if(parent->l == NULL && parent->r != NULL){ //caso ele tenha um filho direito
			if(parent->parent->data.cpf > parent->data.cpf){ // verifico se ele � o filho esquerdo do pai 

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
				tree*aux; // variavel auxiliar para movimenta��o

			if(parent->parent->data.cpf > parent->data.cpf){ // verifico se ele � o filho esquerdo do pai 
				
				aux = parent->r; // atribuo a aux o filho direito do pai
				parent->parent->l = parent->r; // atribuo ao filho esquerdo do avo o filho direito do pai

				while (aux->l != NULL ) // enquanto n�o encontrar um filho esquerdo que seja nulo, ou seja, que possa ser inserida uma folha
				{
					aux = aux->l; // aux recebe o seu galho esquerdo 
				}

				aux->l = parent->l; //atribuo ao filho esquerdo de aux o filho esquerdo do pai
				

				
			}
			else{ // caso seja o filho direito
				aux =parent->l; // atribuo a aux o filho esquerdo do parente
				parent->parent->r = parent->l;//atribuo ao lado direito do avo o filho esquerdo do pai 
				
				while(aux->r != NULL){ //enquanto n�o achar um filho direito que seja nulo, ou seja, onde d� pra inserir uma folha
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
			rotate(root);//faz a rota��o
		}

		else if (abs( (*root)->bal) > abs(before_bal)) // se o fator de balanceamento atual for maior que o anterior em modulo
		{
			balancing_factor(&((*root)->parent), '-'); // chama a fun��o de maneira recursiva e passa como sinal -, para subtrair uma unidade do balanceamento do pai
		}
		else if(abs( (*root)->bal) < abs(before_bal)){ // se for menor que o anterior
			balancing_factor(&((*root)->parent), '+'); //passa como sinal +, para adicionar uma unidade no fator de balanceamento do pai
		}
		break;

	case '+'://caso seja um filho direito
		(*root)->bal++;//adiciona uma unidade ao fator de balancemanto

		if(abs((*root)->bal) == 2){ // verifica se o fator de balanceamento � igual a 2 em modulo
			rotate(root);//caso seja, faz a rota��o
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
	tree*aux = (*root)->parent;//variavel auxiliar guarda o avo

	//se o desbalancemento do avo for para a esquerda e o pai tiver um filho esquerdo
	if((*root)->bal == -2 && (*root)->l->bal == -1){
		
	rotate_right(root); //fa�o a rota��o pra esquerda com o pai e neto
	
	aux->l = (*root)->parent; //informo ao avo que o neto agora � o novo filho esquerdo
	
	}

	//se  o desbalanceamento do avo for  para a direita e o pai tiver um filho direito
	else if((*root)->bal == 2 && (*root)->r->bal == 1){ 
	
	rotate_left(root); // fa�o a rota��o do pai com o neto
	
	aux->r = (*root)->parent;//informo ao avo que o neto � o novo filho
	
	}
	
	
	//se o desbalanceamento do avo for pra esquerda e o pai tiver um filho direito
	else if((*root)->bal == -2 && (*root)->r == 1){
		rotate_left(&((*root)->l));//troco a folha com o neto
		(*root)->l = (*root)->l->parent;
		rotate_right(root);
		aux->l =  (*root)->parent;

	}
	
	//se o desbalanceamento do avo for para a direita e o pai tiver um filho esquerdo
	else if ((*root)->bal == 2 && (*root)->l == -1){
		rotate_right(&((*root)->r)); //troco a folha com o neto
		(*root)->r = (*root)->r->parent;//falo pro pai que a folha � o novo neto
		rotate_left(root);//troco o pai com a folha
		aux->r = (*root)->parent; //falo pra avo que o folha � o novo filho 
	}
}

void rotate_left(tree **root)
{
	(*root)->r->l = (*root);//fa�o a troca do pai direito com o filho direito
	(*root)->r->parent =  (*root)->parent;
	(*root)->parent = (*root)->r;//informo ao pais que o filho � o novo pai;
	
}

void rotate_right(tree **root)
{
	(*root)->l->r = (*root);//fa�o a troca do pai esquerdo com o filho esquerdo
	(*root)->l->parent = (*root)->parent; //informo ao neto que o avo � o seu pai
	(*root)->parent = (*root)->l;//informo ao pai que o filho � o novo pai
}

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"



tree * search(tree * root, int id){
	if (tree.data.cpf == id){
		return tree;
	}
	else if(tree.data.cpf < id)
		return search(tree.r, id);
	else
		return search(tree.l, id);
}


int insert(tree ** root, typedata data){
	tree*leaf = (tree*) malloc(sizeof(tree));
	tree*parent = *root
	
	leaf->l = NULL;//aterro 
	leaf->r = NULL;//aterro o lado esquerdo da folha
	
	leaf.data = data;
	leaf.bal = 0;
	
	if(*root){ // se a raiz não for nula 
		while(parent.r != NULL || parent.l != NULL){ //enquanto não chegar em uma folha o loop repete
			if (parent.data.cpf > data.cpf)
				parent = parent.l;
			else
				parent = parent.r;
		}
		
		if (parent.data.cpf > data)
			parent.l = leaf;
			parent.bal --;
		
		else
			parent.r = leaf;
			
		leaf.parent = parent;
	}
	else{
		*root = leaf;
		leaf.parent = NULL;
	}
}

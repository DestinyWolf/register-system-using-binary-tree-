include <stdlib.h> // biblioteca de gerenciamento de memoria
#include <stdio.h> //biblioteca de funções de entrada e saida basicas do C
#include <conio.h>
#include "tree.h" //biblioteca da TAD

//função principal, cria a raiz da arvore e chama o menu principal da aplicação
void main(){
	tree *root = (tree*) malloc(sizeof(tree)); //criação da raiz da arvore
	
	menu(&tree); //chamada do menu
	
}

//função do menu principal, mostra as possiveis escolhas do usuario, e a partir de sua escolha, chama uma das funções disponveis
void menu(tree**root){
	int opc;
	
	
	printf("selecione uma das opcoes disponiveis: \n");
	printf("1 -> cadastrar nova pessoa\n2 -> buscar pessoa\n3 -> remover\nEscolha: ");
	opc = getch();
	
	switch(opc){
		case 1: cadastro(root);//chamada da função cadastro
			break;
		case 2: buscar(root); //chamada da função de busca
			break;
		case 3: remover(root); // chamada da função de remoção
			break
		default: print("Opcao indisponivel\n"); // caso não seja nenhuma das anteriores o programa retorna para o menu;
			menu(root);
			break;
	}
}

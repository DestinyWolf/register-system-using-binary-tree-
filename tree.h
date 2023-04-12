#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#define true 1;
#define false 0;

//cria��o do registro dos dados dos usuarios
typedef struct typedata{
    int cpf; //cpf 14 caracterss
    char nome[64]; // nome 
    int dia, mes, ano; // data de nascimento
    int numero, ddd; //numero de telefone e ddd

}typedata; // defini��o do "apelido" do registro

//criaçãoo do registro da arvore
typedef struct tree{
    typedata data; //campo destinado a guardar os dados do registro data
	
	int bal;
    struct tree *l; //galho a esquerda
    struct tree *r;//galho a direita
    struct tree *parent; // galho pai 
}tree;

/// @brief busca e retorna, a partir de uma chave, o galho/ folha deseja, busca ocorre de maneira recursiva
/// @param root 
/// @param id
/// @return galho / folha contendo o dado desejado
tree * search(tree * root, int id);

/// @brief adiciona uma nova folha a arvore binaria
/// @param root 
/// @param data 
/// @return true ou false, dependendo se a opera��o foi realizada ou n�o
int insert(tree ** root, typedata data);

/// @brief remove uma folha ou um galho da arvore binaria
/// @param root 
/// @param id
/// @return true ou false, dependendo se a opera��o foi realizada ou n�o
int remove(tree ** root, int id);


/// @brief atualiza o fator de balanceamento e chama a função de rotação
/// @param root 
void balancing_factor(tree**root, char sign);

/// @brief faz o rotacionamento da arvore e de subarvores
/// @param root 
void rotate(tree ** root);

/// @brief faz o rotacionamento para a esquerda
/// @param root 
void rotate_left(tree**root);

/// @brief faz o rotacionamento para a direita
/// @param root 
void rotate_right(tree**root);

#endif //TREE_H_INCLUDED

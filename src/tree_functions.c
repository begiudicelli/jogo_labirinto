#include "labirinto.h"

TreeNode* createNode(int value) {
	TreeNode *newNode = (TreeNode*) malloc(sizeof(TreeNode));
	newNode->value = value;
	newNode->right = NULL;
	newNode->left = NULL;
	newNode->parent = NULL;
	return newNode;
}

TreeNode* insertTreeNode(TreeNode *root, int value) {
	if (root == NULL)
		return createNode(value);

	if (value > root->value) {
		root->right = insertTreeNode(root->right, value);
		root->right->parent = root;
	} else {
		root->left = insertTreeNode(root->left, value);
		root->left->parent = root;
	}
	return root;
}

TreeNode* createPuzzle(int size) {
	TreeNode *root = NULL;
	root = insertTreeNode(root, 10);
	root = insertTreeNode(root, 8);
	root = insertTreeNode(root, 12);
	root = insertTreeNode(root, 6);
	root = insertTreeNode(root, 15);
	root = insertTreeNode(root, 13);
	return root;
}

/*TreeNode* createPuzzle(int size) {
 TreeNode *root = NULL;
 for(int i = 0; i < size; i++){
 int value = rand() % 100;
 root = insertTreeNode(root, value);
 }
 return root;
 }*/

void printTree(TreeNode* root){
	if(root != NULL){
		printf("\nAtual %p - Código %d - Esquerda %p - Direita - %p",
						root, root->value, root->left, root->right);
		printTree(root->left);
		printTree(root->right);
	}
}

void play(TreeNode *node, int answer) {
    while (node != NULL) {
        if (node->value == answer) {
            printf("Você chegou no tesouro!\n");
            return;
        }
        printf("Você está em um nó com o valor: %d\n", node->value);

        if (node->right == NULL && node->left == NULL) {
            printf("Encontrou um beco sem saída! Voltando para trás...\n");
            node = node->parent;
            continue;
        }

        if (node->right == NULL) {
            printf("Não há caminho para a direita. Retornar ou ir para a esquerda?\n");
            char escolha;
            printf("Escolha (e/v): ");
            scanf(" %c", &escolha);
            if (escolha == 'e') {
                node = node->left;
            } else {
                node = node->parent;
            }
            continue;
        }

        if (node->left == NULL) {
            printf("Não há caminho para a esquerda. Retornar ou ir para a direita?\n");
            char escolha;
            printf("Escolha (d/v): ");
            scanf(" %c", &escolha);
            if (escolha == 'd') {
                node = node->right;
            } else {
                node = node->parent;
            }
            continue;
        }

        char escolha;
        printf("Escolha (e/d): ");
        scanf(" %c", &escolha);

        if (escolha == 'e') {
            node = node->left;
        } else if (escolha == 'd') {
            node = node->right;
        } else {
            printf("Escolha inválida! Tente novamente.\n");
            node = node->parent;
        }
    }
    printf("Você saiu do labirinto sem encontrar o tesouro!\n");
}








#include "labirinto.h"

int nextId = 1;

Room* createRoom(const char *description) {
	Room *newRoom = (Room*) malloc(sizeof(Room));
	newRoom->id = nextId++;
	newRoom->description = strdup(description);
	newRoom->right = NULL;
	newRoom->left = NULL;
	newRoom->parent = NULL;
	return newRoom;
}

void insertChildRoom(Room *parent, Room *child, int side){
	if(side == 0){
		if(parent->left == NULL){
			parent->left = child;
			child->parent = parent;
		}else{
			printf("Ja existe uma sala a esquerda.\n");
		}
	}else if(side == 1){
		if(parent->right == NULL){
			parent->right = child;
			child->parent = parent;
		}else{
			printf("Ja existe uma sala a direita.\n");
		}
	}else{
		printf("Lado invalido.0 para esquerda e 1 para direita");
	}
}

Room* createPuzzle() {
	Room *inicialRoom = createRoom("Primeira sala!");
	Room *secondRoom = createRoom("Sala a esquerda da priemeira.");
	Room *thirdRoom = createRoom("Sala a direita da primeira.");
	insertChildRoom(inicialRoom, secondRoom, 0);
	insertChildRoom(inicialRoom, thirdRoom, 1);

	return inicialRoom;
}

/*
TreeNode* createPuzzle(int size) {
 TreeNode *root = NULL;
 for(int i = 0; i < size; i++){
 int value = rand() % 100;
 root = insertTreeNode(root, value);
 }
 return root;
 }

void printTree(TreeNode* root){
	if(root != NULL){
		printf("\nAtual %p - Código %d - Esquerda %p - Direita - %p",
						root, root->value, root->left, root->right);
		printTree(root->left);
		printTree(root->right);
	}
}

void displayRoom(TreeNode* node){
	switch(node->value){
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
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
*/








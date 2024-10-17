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
	Room *inicialRoom = createRoom("Voce acorda em uma caverna\nEsquerda: Tunel | Direita: Porta.\n");

	Room *tunel = createRoom("Voce entrou no tunel\nEsquerda: Pegar o trem | Direita: Entrar no lago.\n");
	Room *door = createRoom("Voce entrou na porta\nEsquerda: Conversar com o guarda | Direita: Seguir pelo corredor\n");

	Room *trem = createRoom("Voce entra no trem\nEsquerda: NULO | Direita: NULO\n");
	Room *lake = createRoom("Voce entra no lago\nEsquerda: NULO | Direita: NULO\n");

	Room *guard = createRoom("Voce conversa com o guarda\nEsquerda: NULO | Direita: NULO.\n");
	Room *corredor = createRoom("Voce segue pelo corredor\nEsquerda: NULO | Direita: NULO.\n");

	insertChildRoom(inicialRoom, tunel, 0);
	insertChildRoom(inicialRoom, door, 1);

	insertChildRoom(tunel, trem, 0);
	insertChildRoom(tunel, lake, 1);

	insertChildRoom(door, guard, 0);
	insertChildRoom(door, corredor, 1);

	return inicialRoom;
}

void chooseRoom(Room *currentRoom){
	char choose;
	while(1){
		printf("%s\n", currentRoom->description);
		printf("Ir para esquerda, direita ou voltar?");
		scanf(" %c", &choose);

		if(choose == 'E'){
			currentRoom = currentRoom->left;
		}
		else if(choose == 'D'){
			currentRoom = currentRoom->right;
		}
		else if (choose == 'V'){
			currentRoom = currentRoom->parent;
		}
		else{
			printf("Opcao invalida\n");
		}
	}

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








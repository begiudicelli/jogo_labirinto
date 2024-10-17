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
	Room *inicialRoom = createRoom(loadDescription("src/rooms/inicial_room.txt"));

	Room *tunel = createRoom(loadDescription("src/rooms/tunel.txt"));
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

void chooseRoom(Room **currentRoom) {
    char choose;
    while (true) {
        if (*currentRoom != NULL) {
            printf("%s\n", (*currentRoom)->description);
            printf("Escolha uma opção: (E) - esquerda, (D) - direita, (V) - voltar\n");
            scanf(" %c", &choose);

            if (choose == 'E') {
                if ((*currentRoom)->left != NULL) {
                    *currentRoom = (*currentRoom)->left;
                } else {
                    printf("Não há sala à esquerda.\n");
                }
            } else if (choose == 'D') {
                if ((*currentRoom)->right != NULL) {
                    *currentRoom = (*currentRoom)->right;
                } else {
                    printf("Não há sala à direita.\n");
                }
            } else if (choose == 'V') {
                if ((*currentRoom)->parent != NULL) {
                    *currentRoom = (*currentRoom)->parent;
                } else {
                    printf("Não há mais salas para retornar.\n");
                }
            } else {
                printf("Opcao invalida\n");
            }
        } else {
            printf("Sala não encontrada. Encerrando...\n");
            break;
        }
    }
}

char* loadDescription(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *description = malloc(length + 1);
    if (description) {
        fread(description, 1, length, file);
        description[length] = '\0';
    }

    fclose(file);
    return description;
}

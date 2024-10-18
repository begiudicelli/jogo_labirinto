#include "labirinto.h"

int nextId = 1;

void collectItem(Room *room, Player *player) {
	if (room->items != NULL) {
		Item *itemToCollect = room->items;
		room->items = room->items->next;
		itemToCollect->next = player->inventory;
		player->inventory = itemToCollect;
		printf("Você coletou: %s\n", itemToCollect->name);
	} else {
		printf("Não há itens nesta sala.\n");
	}
}

void addItemToRoom(Room *room, Item item) {
	if (room == NULL) return;
	Item *newItem = createItemList(item.id, item.name);
	newItem->next = room->items;
	room->items = newItem;
}

Item* createItemList(int id, char *name) {
	Item *newItem = (Item*) malloc(sizeof(Item));
	newItem->id = id;
	newItem->name = strdup(name);
	newItem->next = NULL;
	return newItem;
}

Room* createRoom(const char *description, const char *secondDescription) {
	Room *newRoom = (Room*) malloc(sizeof(Room));
	newRoom->id = nextId++;
	newRoom->description = strdup(description);
	newRoom->secondDescription = strdup(secondDescription);
	newRoom->right = NULL;
	newRoom->left = NULL;
	newRoom->parent = NULL;
	newRoom->items = NULL;
	newRoom->requiredItemId = 0;
	newRoom->visited = false;
	return newRoom;
}

Room* createRoomWithRequiredItem(const char *description, const char *secondDescription ,int requiredItemId) {
	Room *newRoom = createRoom(description, secondDescription);
	newRoom->requiredItemId = requiredItemId;
	return newRoom;
}

bool playerHasItem(Player *player, int itemId) {
	Item *current = player->inventory;
	while (current != NULL) {
		if (current->id == itemId) {
			return true;
		}
		current = current->next;
	}
	return false;
}

void insertChildRoom(Room *parent, Room *child, int side) {
	if (side == 0) {
		if (parent->left == NULL) {
			parent->left = child;
			child->parent = parent;
		} else {
			printf("Ja existe uma sala a esquerda.\n");
		}
	} else if (side == 1) {
		if (parent->right == NULL) {
			parent->right = child;
			child->parent = parent;
		} else {
			printf("Ja existe uma sala a direita.\n");
		}
	} else {
		printf("Lado invalido.0 para esquerda e 1 para direita");
	}
}

Room* createPuzzle() {
	Room *inicialRoom = createRoom(loadDescription("src/rooms/inicial_room.txt"),
			loadDescription("src/rooms/inicial_room2.txt"));

	Room *tunel = createRoom(loadDescription("src/rooms/newtunel.txt"),
			loadDescription("src/rooms/tunel2.txt"));
	Room *door =createRoomWithRequiredItem("Voce entrou na porta\n",
			"JA PASSOU AQUI", 1);

	Room *trem = createRoom("Voce entra no trem\nEsquerda: NULO | Direita: NULO\n",
			"JA PASSOU AQUI");
	Room *lake = createRoom(loadDescription("src/rooms/lake_key.txt"),
			loadDescription("src/rooms/lake_key2.txt"));

	Room *guard = createRoom("Voce conversa com o guarda\nEsquerda: NULO | Direita: NULO.\n",
			"JA PASSOU AQUI");
	Room *corredor = createRoom("Voce segue pelo corredor\nEsquerda: NULO | Direita: NULO.\n",
			"JA PASSOU AQUI");


	insertChildRoom(inicialRoom, tunel, 0);
	insertChildRoom(inicialRoom, door, 1);

	insertChildRoom(tunel, trem, 0);
	insertChildRoom(tunel, lake, 1);

	insertChildRoom(door, guard, 0);
	insertChildRoom(door, corredor, 1);

	Item key = { 1, "Chave", NULL };
	addItemToRoom(lake, key);

	return inicialRoom;
}

void chooseRoom(Room **currentRoom, Player *player) {
	char choose;
	while (true) {
		if (*currentRoom != NULL) {
			if(!(*currentRoom)->visited){
				printf("%s\n", (*currentRoom)->description);
				(*currentRoom)->visited = true;
			}else{
				printf("%s\n", (*currentRoom)->secondDescription);
			}
			collectItem(*currentRoom, player);
			scanf(" %c", &choose);

			if (choose == 'E') {
				if ((*currentRoom)->left != NULL) {
					Room *nextRoom = (*currentRoom)->left;
					if (nextRoom->requiredItemId != 0 && !playerHasItem(player,nextRoom->requiredItemId)) {
						printf("Você precisa de um item específico para acessar esta sala.\n");
					}else {
                        *currentRoom = nextRoom;
                    }
				} else {
					printf("Não há sala à esquerda.\n");
				}
			} else if (choose == 'D') {
				if ((*currentRoom)->right != NULL) {
					Room *nextRoom = (*currentRoom)->right;
					if(nextRoom->requiredItemId !=0 && !playerHasItem(player,nextRoom->requiredItemId)){
						printf("Você precisa de um item específico para acessar esta sala.\n");
					}else {
                        *currentRoom = nextRoom;
                    }
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

void trimTrailingSpaces(char *str) {
    int length = strlen(str);
    while (length > 0 && (str[length - 1] == ' ' || str[length - 1] == '\n' || str[length - 1] == '\r')) {
        str[--length] = '\0';
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
        size_t bytesRead = fread(description, 1, length, file);
        description[bytesRead] = '\0';
        trimTrailingSpaces(description);
    } else {
        perror("Erro ao alocar memória");
    }

    fclose(file);
    return description;
}




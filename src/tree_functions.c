#include "labirinto.h"

int nextId = 1;

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
	newRoom->enemy = NULL;
	newRoom->spell = NULL;
	return newRoom;
}

Room* createRoomWithRequiredItem(const char *description,
		const char *secondDescription, int requiredItemId) {
	Room *newRoom = createRoom(description, secondDescription);
	newRoom->requiredItemId = requiredItemId;
	return newRoom;
}

Room* createRoomWithEnemy(const char *description,
		const char *secondDescription, Enemy *enemy) {
	Room *newRoom = createRoom(description, secondDescription);
	newRoom->enemy = enemy;
	return newRoom;
}

void insertChildRoom(Room *parent, Room *child, int side) {
	if (side == 0) {
		if (parent->left == NULL) {
			parent->left = child;
			child->parent = parent;
		} else {
			printf("Já existe uma sala à esquerda.\n");
		}
	} else if (side == 1) {
		if (parent->right == NULL) {
			parent->right = child;
			child->parent = parent;
		} else {
			printf("Já existe uma sala à direita.\n");
		}
	} else {
		printf("Lado inválido. 0 para esquerda e 1 para direita.\n");
	}
}

Room* createPuzzle() {
	Room *inicialRoom = createRoom(
			loadDescription("src/rooms/inicial_room.txt"),
			loadDescription("src/rooms/inicial_room2.txt"));

	Room *tunel = createRoom(loadDescription("src/rooms/newtunel.txt"),
			loadDescription("src/rooms/tunel2.txt"));
	Room *door = createRoomWithRequiredItem(
			loadDescription("src/rooms/door.txt"),
			loadDescription("src/rooms/door2.txt"), 1);
	Room *trem = createRoom(
			"Você entra no trem\nEsquerda: Investigar trem | Direita: \n",
			"Já passou aqui");

	Room *lake = createRoom(loadDescription("src/rooms/lake_key.txt"),
			loadDescription("src/rooms/lake_key2.txt"));

	Enemy *goblin = createEnemy(1, "Goblin", 100, 5);
	Room *goblinRoom = createRoomWithEnemy("Goblin Room\n",
			"Voce retorna a sala do slime.\n", goblin);

	Enemy *slime = createEnemy(2, "Slime", 80, 8);
	Room *slimeRoom = createRoomWithEnemy("Slime Room\n",
			"Voce retorna a sala do slime.\n", slime);

	insertChildRoom(inicialRoom, tunel, 0);
	insertChildRoom(inicialRoom, door, 1);
	insertChildRoom(tunel, trem, 0);
	insertChildRoom(tunel, lake, 1);
	insertChildRoom(door, goblinRoom, 0);
	insertChildRoom(door, slimeRoom, 1);

	Item key = { 1, "Chave", NULL };
	addItemToRoom(lake, key);

	Spell *fireball = createSpell(1, "Fireball", 2, 20, 10);
	addSpellToRoom(door, fireball);

	return inicialRoom;
}

void moveRoom(Room **currentRoom, Player *Player, int side) {
	if (side == 0) {
		if ((*currentRoom)->left != NULL) {
			Room *nextRoom = (*currentRoom)->left;
			*currentRoom = nextRoom;
		} else {
			printf("Nao há sala a esquerda\n;");
		}
	} else {
		if ((*currentRoom)->right != NULL) {
			Room *nextRoom = (*currentRoom)->right;
			*currentRoom = nextRoom;
		} else {
			printf("Não ha sala a direita\n");
		}
	}
}

bool checkRoomForSpell(Room **currentRoom, Player *player) {
	if ((*currentRoom)->spell != NULL) {
		printf("New spell found!: %s\n", (*currentRoom)->spell->name);
		return true;
	} else {
		printf("No spell in this room.\n");
		return false;
	}
}

bool checkRoomForItem(Room *currentRoom, Player *player) {
	if (currentRoom->requiredItemId != 0
			&& !playerHasItem(player, currentRoom->requiredItemId)) {
		printf("Você precisa de um item específico para acessar esta sala.\n");
		return false;
	} else {
		return true;
	}
}

bool checkRoomForEnemy(Room **currentRoom) {
	if ((*currentRoom)->enemy != NULL) {
		printf("Enemy found: %s\n", (*currentRoom)->enemy->name);
		return true;
	} else {
		printf("No enemy found in this room.\n");
		return false;
	}
}

void chooseRoom(Room **currentRoom, Player *player) {
	char choose;
	while (true) {
		printDescription(currentRoom);
		collectItem(*currentRoom, player);
		printInventory(player->inventory);
		scanf(" %c", &choose);

		switch (choose) {
		case 'E':
			//if(checkRoomForItem((*currentRoom)->left, player)){
				moveRoom(currentRoom, player, 0);

				if(checkRoomForSpell(currentRoom, player)){
					addSpellToBar(player, (*currentRoom)->spell);
				}

		        if (checkRoomForEnemy(currentRoom)) {
		            battle(player, currentRoom);
		        }
			//
			break;
		case 'D':
			//if(checkRoomForItem((*currentRoom)->right, player)){
				moveRoom(currentRoom, player, 1);

				if(checkRoomForSpell(currentRoom, player)){
					addSpellToBar(player, (*currentRoom)->spell);
				}

		        if (checkRoomForEnemy(currentRoom)) {
		            battle(player, currentRoom);
		        }
			//}
			break;
		break;
		case 'V':
			if ((*currentRoom)->parent != NULL) {
				*currentRoom = (*currentRoom)->parent;
			} else {
				printf("Não há mais salas para retornar.\n");
			}
			break;
		default:
			printf("Opção inválida.\n");
			break;
		}
	}

}

void printDescription(Room **currentRoom) {
	if (*currentRoom != NULL) {
		if (!(*currentRoom)->visited) {
			printf("%s\n", (*currentRoom)->description);
			(*currentRoom)->visited = true;
		} else {
			printf("%s\n", (*currentRoom)->secondDescription);
		}
	}
}


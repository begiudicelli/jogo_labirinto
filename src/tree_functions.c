#include "labirinto.h"

int nextId = 1;

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

Room* createRoomWithRequiredItem(const char *description,
                                  const char *secondDescription, int requiredItemId) {
    Room *newRoom = createRoom(description, secondDescription);
    newRoom->requiredItemId = requiredItemId;
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
        loadDescription("src/rooms/inicial_room2.txt")
    );

    Room *tunel = createRoom(
        loadDescription("src/rooms/newtunel.txt"),
        loadDescription("src/rooms/tunel2.txt")
    );
    Room *door = createRoomWithRequiredItem(
        loadDescription("src/rooms/door.txt"),
        loadDescription("src/rooms/door2.txt"),
        1
    );
    Room *trem = createRoom(
        "Você entra no trem\nEsquerda: Investigar trem | Direita: \n",
        "Já passou aqui"
    );
    Room *lake = createRoom(
        loadDescription("src/rooms/lake_key.txt"),
        loadDescription("src/rooms/lake_key2.txt")
    );

    Room *guard = createRoom(
        "goblin nulo e nulo\n",
        "goblin nulo e nulo\n"
    );
    Room *corredor = createRoom(
        "slime nulo e nulo\n",
        "slime nulo e nulo\n"
    );

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

void moveToRoomAndCheckItem(Room **currentRoom, Player *player, int side){
	if(side == 0){
	    if ((*currentRoom)->left != NULL) {
	        Room *nextRoom = (*currentRoom)->left;
	        if (nextRoom->requiredItemId != 0
	            && !playerHasItem(player, nextRoom->requiredItemId)) {
	            printf("Você precisa de um item específico para acessar esta sala.\n");
	        } else {
	            *currentRoom = nextRoom;
	        }
	    } else {
	        printf("Não há sala à esquerda.\n");
	    }
	}else{
        if ((*currentRoom)->right != NULL) {
            Room *nextRoom = (*currentRoom)->right;
            if (nextRoom->requiredItemId != 0
                && !playerHasItem(player, nextRoom->requiredItemId)) {
                printf("Você precisa de um item específico para acessar esta sala.\n");
            } else {
                *currentRoom = nextRoom;
            }
        } else {
            printf("Não há sala à direita.\n");
        }
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
                moveToRoomAndCheckItem(currentRoom, player, 0);
                break;
            case 'D':
            	moveToRoomAndCheckItem(currentRoom, player, 1);
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


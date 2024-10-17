#ifndef LABIRINTO_H_
#define LABIRINTO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct LinkedList{
	int id;
	char *name;
	struct LinkedList *next;
}Item;

typedef struct TreeNode{
	int id;
	char *description;
	char *secondDescription;
	struct TreeNode *left;
	struct TreeNode *right;
	struct TreeNode *parent;
	Item *items;
	int requiredItemId;
	bool visited;
}Room;

typedef struct Player {
    Item *inventory;
} Player;


Room* createRoom(const char *description, const char *secondDescription);
void insertChildRoom(Room *parent, Room *child, int side);
Room* createPuzzle();
void displayRoom(Room* room);
void chooseRoom(Room **currentRoom, Player *player);
Item* createItemList(int id, char *name);
void insertItem(Item** head, int id, char *name);


char* loadDescription(const char *filename);

#endif

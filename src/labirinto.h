#ifndef LABIRINTO_H_
#define LABIRINTO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct TreeNode{
	int id;
	char *description;
	struct TreeNode *left;
	struct TreeNode *right;
	struct TreeNode *parent;
}Room;


Room* createRoom(const char *description);
void insertChildRoom(Room *parent, Room *child, int side);
Room* createPuzzle();
void displayRoom(Room* room);
void chooseRoom(Room **currentRoom);

char* loadDescription(const char *filename);

#endif

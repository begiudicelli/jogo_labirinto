#ifndef LABIRINTO_H_
#define LABIRINTO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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


#endif

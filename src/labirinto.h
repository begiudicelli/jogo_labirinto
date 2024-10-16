#ifndef LABIRINTO_H_
#define LABIRINTO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct TreeNode{
	int value;
	struct TreeNode *left;
	struct TreeNode *right;
	struct TreeNode *parent;
}TreeNode;


TreeNode* createNode(int value);
TreeNode* createPuzzle(int size);
void play(TreeNode *node, int answer);
void printTree(TreeNode* root);

#endif

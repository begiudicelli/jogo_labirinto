#ifndef LABIRINTO_H_
#define LABIRINTO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct Item {
	int id;
	char *name;
	struct Item *next;
} Item;

typedef struct Spell {
	int id;
	char *name;
	int cooldown;
	double damage;
	double mana;
	double cost;
} Spell;

typedef struct Player {
	double health;
	double mana;
	Item *inventory;
	Spell *spellBar;
	int spellCount;
} Player;

typedef struct Enemy {
	int id;
	char *name;
	double health;
	double attack;
} Enemy;

typedef struct TreeNode {
	int id;
	char *description;
	char *secondDescription;
	struct TreeNode *left;
	struct TreeNode *right;
	struct TreeNode *parent;
	Item *items;
	int requiredItemId;
	bool visited;
	Enemy *enemy;
} Room;

//Room functions
Room* createRoom(const char *description, const char *secondDescription);
Room* createRoomWithEnemy(const char *description, const char *secondDescription,Enemy *enemy);
void insertChildRoom(Room *parent, Room *child, int side);
Room* createPuzzle();
void displayRoom(Room *room);
void chooseRoom(Room **currentRoom, Player *player);
void moveToRoomAndCheckItem(Room **currentRoom, Player *player, int side);
bool checkRoomForEnemy(Room **currentRoom);

//Inventory and item functions
Item* createItemList(int id, char *name);
void insertItem(Item **head, int id, char *name);
void printDescription(Room **currentRoom);
void printInventory(Item *inventory);
void collectItem(Room *room, Player *player);
void addItemToRoom(Room *room, Item item);
Item* createItemList(int id, char *name);
bool playerHasItem(Player *player, int itemId);

//Battle
Spell* createSpell(int id, const char *name, int cooldown);
void addSpellToBar(Player *player, Spell *spell);
Player* createPlayer(double health, double mana);
Enemy* createEnemy(int id, const char *name, double health, double attack);
void battle(Player *player, Room **currentRoom);

//File handling
char* loadDescription(const char *filename);

#endif

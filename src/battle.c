#include "labirinto.h"
#define MAX_SPELLS 10

Player* createPlayer(double health, double mana){
	Player *newPlayer = (Player *) malloc(sizeof(Player));
	newPlayer->health = health;
	newPlayer->mana = mana;
	newPlayer->inventory = NULL;
	newPlayer->spellBar = (Spell *)malloc(MAX_SPELLS * sizeof(Spell));
	newPlayer->spellCount = 0;
	return newPlayer;
}

Enemy* createEnemy(int id, const char *name, double health, double attack){
	Enemy *newEnemy = (Enemy *)malloc(sizeof(Enemy));
	newEnemy->id = id;
	newEnemy->name = strdup(name);
	newEnemy->health = health;
	newEnemy->attack = attack;
	return newEnemy;
}

Spell* createSpell(int id, const char *name, int cooldown) {
    Spell *newSpell = (Spell *)malloc(sizeof(Spell));
    newSpell->id = id;
    newSpell->name = strdup(name);
    newSpell->cooldown = cooldown;
    return newSpell;
}

void addSpellToBar(Player *player, Spell *spell){
	player->spellBar[player->spellCount++] = *spell;
}



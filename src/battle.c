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

void playerAttack(Player *player, Enemy *enemy, int spellIndex){
	if(spellIndex < 0 || spellIndex >= player->spellCount){
		printf("Spell invalido!\n");
		return;
	}

	Spell *spell = &player->spellBar[spellIndex];

	if(player->mana >= spell->cost){
		player->mana -= spell->cost;
		enemy->health -= spell->damage;
		printf("voce lanca o feitico %s causando %2.f de dano!", spell->name, spell->damage);
	}else{
		printf("Nao tem mana para usar o feitico %s", spell->name);
	}
}

void enemyAttack(Player *player, Enemy *enemy){
	player->health -= enemy->attack;
	printf("%s te ataca causando %.2f de dano\n", enemy->name, enemy->attack);

}


void battle(Player *player, Room **currentRoom) {
    int turn = 0;
    Enemy *enemy = (*currentRoom)->enemy;

    while (player->health > 0 && enemy) {
        if (turn == 0) {
            printf("Seu turno!\n");
            printf("Escolha um spell (0 até %d): ", player->spellCount - 1);
            for (int i = 0; i < player->spellCount; i++) {
                printf("%d: %s (Cooldown: %d, Dano: %.2f)\n", i,
                       player->spellBar[i].name,
                       player->spellBar[i].cooldown,
                       player->spellBar[i].damage);
            }
            int spellIndex;
            scanf("%d", &spellIndex);
            playerAttack(player, enemy, spellIndex);
        } else {
            printf("\nTurno do inimigo!\n");
            enemyAttack(player, enemy);
        }

        if (enemy->health <= 0) {
            printf("%s foi derrotado!\n", enemy->name);
            (*currentRoom)->enemy = NULL; // Clear the enemy after defeat
            break;
        } else if (player->health <= 0) {
            printf("Você foi derrotado!\n");
            break;
        }

        turn = 1 - turn;
    }
}




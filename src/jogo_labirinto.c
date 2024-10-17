#include "labirinto.h"

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	srand(time(NULL));

	Player *player = (Player *)malloc(sizeof(Player));
	player->inventory = NULL;
	Room *puzzle = createPuzzle();
	chooseRoom(&puzzle, player);

	return 0;
}


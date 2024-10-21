#include "labirinto.h"

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	srand(time(NULL));

	Player *player = createPlayer(100, 100);
	Room *puzzle = createPuzzle();
	chooseRoom(&puzzle, player);

	return 0;
}


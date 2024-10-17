#include "labirinto.h"

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	srand(time(NULL));

	Room *puzzle = createPuzzle();
	chooseRoom(&puzzle);

	return 0;
}


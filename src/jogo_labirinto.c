#include "labirinto.h"

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
    srand(time(NULL));

    Room *puzzle = createPuzzle();

    printf("Sala inicial: %d - %s\n", puzzle->id, puzzle->description);
    if (puzzle->left) {
        printf("Sala esquerda: %d - %s\n", puzzle->left->id, puzzle->left->description);
    }
    if (puzzle->right) {
        printf("Sala direita: %d - %s\n", puzzle->right->id, puzzle->right->description);
    }
    return 0;
}

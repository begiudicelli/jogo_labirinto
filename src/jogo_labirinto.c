#include "labirinto.h"

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
    srand(time(NULL));

    int answer = 5;

    TreeNode *labirinto = createPuzzle(6);
    //printTree(labirinto);
    play(labirinto, answer);
    return 0;
}

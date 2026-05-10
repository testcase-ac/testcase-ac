#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There are 5 boards, each 5x5, total 25 lines
    const int N = 5;
    const int BOARD_SIZE = 5;

    for (int board = 0; board < N; ++board) {
        for (int row = 0; row < BOARD_SIZE; ++row) {
            // Read 5 integers in [0,1]
            inf.readInts(BOARD_SIZE, 0, 1, "cell");
            inf.readEoln();
        }
    }

    inf.readEof();
}

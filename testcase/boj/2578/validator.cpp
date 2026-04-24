#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the 5x5 bingo board
    vector<bool> used_board(26, false);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int x = inf.readInt(1, 25, "board");
            if (used_board[x]) {
                ensuref(false, "Duplicate number %d in bingo board at position (%d, %d)", x, i+1, j+1);
            }
            used_board[x] = true;
            if (j < 4) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }
    // Ensure all numbers 1..25 appear exactly once in the board
    for (int x = 1; x <= 25; x++) {
        ensuref(used_board[x], "Number %d is missing from the bingo board", x);
    }

    // Read the 5x5 sequence of called numbers
    vector<bool> used_call(26, false);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int x = inf.readInt(1, 25, "call");
            if (used_call[x]) {
                ensuref(false, "Duplicate called number %d at position (%d, %d) in calls", x, i+1, j+1);
            }
            used_call[x] = true;
            if (j < 4) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }
    // Ensure all numbers 1..25 appear exactly once in the calls
    for (int x = 1; x <= 25; x++) {
        ensuref(used_call[x], "Called number %d is missing from the input sequence", x);
    }

    inf.readEof();
    return 0;
}

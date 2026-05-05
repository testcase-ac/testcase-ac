#include "testlib.h"
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <limits>
using namespace std;

// The game board is always 3x4, with 12 cells.
// The problem does not specify the board values, but from the sample, it is implied that
// the board contains the numbers 1..12, arranged in some order, and the sequence to press
// is a sequence of numbers that exist on the board.

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Board is fixed: 3 rows x 4 columns, cells are numbered 1..12, left to right, top to bottom.
    // 1  2  3  4
    // 5  6  7  8
    // 9 10 11 12

    // Map from number to position (row, col)
    map<int, pair<int,int>> num2pos;
    int idx = 1;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 4; ++c) {
            num2pos[idx++] = {r, c};
        }
    }

    // Read N, A, B
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int A = inf.readInt(1, 100, "A");
    inf.readSpace();
    int B = inf.readInt(1, 100, "B");
    inf.readEoln();

    // Read sequence
    vector<int> seq = inf.readInts(N, 1, 12, "press_sequence");
    inf.readEoln();

    // Check that all numbers in the sequence are valid board numbers
    for (int i = 0; i < N; ++i) {
        ensuref(num2pos.count(seq[i]), "Sequence number at index %d (%d) is not a valid board number (1..12)", i, seq[i]);
    }

    // No further input
    inf.readEof();
}

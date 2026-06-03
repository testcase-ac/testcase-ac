#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<string> board(8);
    for (int r = 0; r < 8; ++r) {
        board[r] = inf.readLine("[.#]{8}", format("board[%d]", r + 1));
    }

    ensuref(board[7][0] == '.', "lower-left starting cell must be empty");

    inf.readEof();
}

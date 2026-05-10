#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(2, 100, "n");
    inf.readSpace();
    int m = inf.readInt(2, 100, "m");
    inf.readEoln();

    // Read the board
    vector<string> board(n);
    for (int i = 0; i < n; ++i) {
        board[i] = inf.readLine("[*+.]{"+to_string(m)+","+to_string(m)+"}", "board_row");
        ensuref((int)board[i].size() == m, "Row %d has length %d, expected %d", i+1, (int)board[i].size(), m);
    }

    inf.readEof();
}

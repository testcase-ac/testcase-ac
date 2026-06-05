#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 300000, "K");
    inf.readEoln();

    string moves = inf.readToken("[UDLR]{1,300000}", "moves");
    inf.readEoln();
    inf.readEof();

    ensuref((int)moves.size() == k, "moves length must be K: length=%d K=%d",
            (int)moves.size(), k);

    int row = 0;
    int col = 0;
    for (int i = 0; i < k; ++i) {
        if (moves[i] == 'U') {
            --row;
        } else if (moves[i] == 'D') {
            ++row;
        } else if (moves[i] == 'L') {
            --col;
        } else {
            ++col;
        }

        ensuref(0 <= row && row < n && 0 <= col && col < n,
                "move %d leaves the matrix: row=%d col=%d N=%d", i + 1, row + 1,
                col + 1, n);
    }
}

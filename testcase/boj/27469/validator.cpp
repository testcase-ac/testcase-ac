#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readSpace();
    inf.readInt(1, 100, "k");
    inf.readEoln();

    vector<string> board(n);
    for (int i = 0; i < n; ++i) {
        board[i] = inf.readToken("[.#]{1,100}", "s_i");
        ensuref((int)board[i].size() == m, "row %d length is %d, expected %d",
                i + 1, (int)board[i].size(), m);
        inf.readEoln();
    }

    int rs = inf.readInt(1, n, "r_s");
    inf.readSpace();
    int cs = inf.readInt(1, m, "c_s");
    inf.readEoln();

    int re = inf.readInt(1, n, "r_e");
    inf.readSpace();
    int ce = inf.readInt(1, m, "c_e");
    inf.readEoln();

    ensuref(board[rs - 1][cs - 1] == '.', "start cell (%d, %d) is blocked", rs,
            cs);
    ensuref(board[re - 1][ce - 1] == '.', "end cell (%d, %d) is blocked", re,
            ce);

    inf.readEof();
}

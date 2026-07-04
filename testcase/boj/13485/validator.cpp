#include "testlib.h"

#include <array>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    array<string, 10> board;
    for (int row = 0; row < 10; ++row) {
        board[row] = inf.readToken(format("[.X]{%d}", n), format("row[%d]", row + 1));
        inf.readEoln();
    }
    inf.readEof();

    array<array<bool, 100000>, 10> reachable{};
    ensuref(board[9][0] == '.', "starting cell row 10 column 1 is blocked");
    reachable[9][0] = true;

    for (int column = 0; column + 1 < n; ++column) {
        for (int row = 0; row < 10; ++row) {
            if (!reachable[row][column]) {
                continue;
            }

            for (int delta : {-1, 1}) {
                int nextRow = row + delta;
                if (nextRow < 0 || nextRow >= 10) {
                    nextRow = row;
                }
                if (board[nextRow][column + 1] == '.') {
                    reachable[nextRow][column + 1] = true;
                }
            }
        }
    }

    bool canFinish = false;
    for (int row = 0; row < 10; ++row) {
        canFinish = canFinish || reachable[row][n - 1];
    }
    ensuref(canFinish, "no valid route reaches column %d", n);
}

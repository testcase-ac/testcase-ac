#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;
int maxOperations;
vector<vector<int>> initialBoard;

struct Answer {
    int operations;
};

Answer readAnswer(InStream& stream) {
    vector<vector<int>> board = initialBoard;

    int k = stream.readInt(0, maxOperations, "K");
    for (int op = 1; op <= k; ++op) {
        int y1 = stream.readInt(1, n, format("operation[%d].y1", op).c_str());
        int x1 = stream.readInt(1, n, format("operation[%d].x1", op).c_str());
        int y2 = stream.readInt(1, n, format("operation[%d].y2", op).c_str());
        int x2 = stream.readInt(1, n, format("operation[%d].x2", op).c_str());

        if (y1 > y2) {
            stream.quitf(_wa, "operation %d has y1=%d greater than y2=%d", op, y1, y2);
        }
        if (x1 > x2) {
            stream.quitf(_wa, "operation %d has x1=%d greater than x2=%d", op, x1, x2);
        }

        for (int y = y1 - 1; y <= y2 - 1; ++y) {
            for (int x = x1 - 1; x <= x2 - 1; ++x) {
                board[y][x] ^= 1;
            }
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d operations", k);
    }

    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            if (board[y][x] != 0) {
                stream.quitf(_wa, "coin at row %d column %d remains tails", y + 1, x + 1);
            }
        }
    }

    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 250, "N");
    maxOperations = ((n + 2) / 2) * ((n + 2) / 2);

    initialBoard.assign(n, vector<int>(n, 0));
    for (int y = 0; y < n; ++y) {
        string row = inf.readToken(format("[01]{%d}", n), format("row[%d]", y + 1).c_str());
        for (int x = 0; x < n; ++x) {
            initialBoard[y][x] = row[x] - '0';
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok, "valid operation list with %d operations; jury used %d", participant.operations, jury.operations);
}

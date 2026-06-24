#include "testlib.h"

#include <vector>
using namespace std;

int n, m;

struct Answer {
    int operations;
};

Answer readAnswer(InStream& stream) {
    int k = stream.readInt(0, n * m, "k");
    stream.readEoln();

    vector<vector<int>> board(n, vector<int>(m));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            board[r][c] = (r + c) & 1;
        }
    }

    for (int i = 0; i < k; ++i) {
        int r1 = stream.readInt(1, n, format("operation[%d].r1", i + 1).c_str());
        stream.readSpace();
        int c1 = stream.readInt(1, m, format("operation[%d].c1", i + 1).c_str());
        stream.readSpace();
        int r2 = stream.readInt(1, n, format("operation[%d].r2", i + 1).c_str());
        stream.readSpace();
        int c2 = stream.readInt(1, m, format("operation[%d].c2", i + 1).c_str());
        stream.readEoln();

        if (r1 > r2) {
            swap(r1, r2);
        }
        if (c1 > c2) {
            swap(c1, c2);
        }

        for (int r = r1 - 1; r <= r2 - 1; ++r) {
            for (int c = c1 - 1; c <= c2 - 1; ++c) {
                board[r][c] ^= 1;
            }
        }
    }

    stream.readEof();

    int finalColor = board[0][0];
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (board[r][c] != finalColor) {
                stream.quitf(_wa,
                             "operations do not make all cells equal; cell (%d, %d) differs",
                             r + 1,
                             c + 1);
            }
        }
    }

    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 50, "n");
    m = inf.readInt(1, 50, "m");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.operations > jury.operations) {
        quitf(_wa,
              "too many operations: jury=%d participant=%d",
              jury.operations,
              participant.operations);
    }
    if (participant.operations < jury.operations) {
        quitf(_fail,
              "participant found a better answer: jury=%d participant=%d",
              jury.operations,
              participant.operations);
    }

    quitf(_ok, "operations=%d", participant.operations);
}

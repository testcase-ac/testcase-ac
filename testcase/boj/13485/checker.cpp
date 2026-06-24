#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n;
vector<string> board;

struct Answer {
    int moves;
};

Answer readAnswer(InStream& stream) {
    int p = stream.readInt(0, 50000, "P");
    vector<int> pressed(n, 0);
    long long previousEnd = 0;

    for (int i = 0; i < p; ++i) {
        long long t = stream.readLong(0LL, (long long)n - 1, format("t[%d]", i + 1));
        long long x = stream.readLong(1LL, 1000000000LL, format("x[%d]", i + 1));
        if (t < previousEnd) {
            stream.quitf(_wa,
                         "move %d starts at %lld before previous move ends at %lld",
                         i + 1,
                         t,
                         previousEnd);
        }
        previousEnd = t + x;

        int from = (int)t;
        int to = (int)min<long long>(n, t + x);
        for (int second = from; second < to; ++second) {
            pressed[second] = 1;
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after move list");
    }

    int row = 9;
    if (board[row][0] != '.') {
        stream.quitf(_wa, "starting cell row 10 column 1 is blocked");
    }

    for (int column = 0; column + 1 < n; ++column) {
        if (pressed[column]) {
            row = max(0, row - 1);
        } else {
            row = min(9, row + 1);
        }

        if (board[row][column + 1] != '.') {
            stream.quitf(_wa,
                         "Barry hits obstacle at row %d column %d after second %d",
                         row + 1,
                         column + 2,
                         column + 1);
        }
    }

    return {p};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100000, "N");
    board.resize(10);
    for (int i = 0; i < 10; ++i) {
        board[i] = inf.readToken(format("[.X]{%d}", n), format("row[%d]", i + 1));
    }

    readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok, "valid move sequence with %d moves", participant.moves);
}

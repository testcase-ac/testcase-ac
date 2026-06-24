#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

int n, m;

struct Answer {
    int length;
};

int distance1(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

Answer readAnswer(InStream& stream) {
    int length = stream.readInt(1, n * m, "snake length");
    stream.readEoln();

    vector<pair<int, int>> cells(length);
    vector<vector<int>> used(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i < length; ++i) {
        int x = stream.readInt(1, n, format("x[%d]", i + 1).c_str());
        stream.readSpace();
        int y = stream.readInt(1, m, format("y[%d]", i + 1).c_str());
        stream.readEoln();

        if (used[x][y]) {
            stream.quitf(_wa, "cell (%d, %d) appears more than once", x, y);
        }
        used[x][y] = 1;
        cells[i] = {x, y};

        if (i > 0 && distance1(cells[i - 1].first, cells[i - 1].second, x, y) != 1) {
            stream.quitf(_wa,
                         "cells %d and %d are not adjacent: (%d, %d), (%d, %d)",
                         i, i + 1, cells[i - 1].first, cells[i - 1].second, x, y);
        }
    }

    if (distance1(cells.front().first, cells.front().second, cells.back().first, cells.back().second) != 1) {
        stream.quitf(_wa,
                     "head and tail are not adjacent: (%d, %d), (%d, %d)",
                     cells.front().first, cells.front().second, cells.back().first, cells.back().second);
    }

    stream.readEof();
    return {length};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 200, "n");
    inf.readSpace();
    m = inf.readInt(2, 200, "m");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.length < jury.length) {
        quitf(_wa,
              "participant snake is shorter than jury snake: participant=%d jury=%d",
              participant.length, jury.length);
    }
    if (participant.length > jury.length) {
        quitf(_fail,
              "participant found a longer valid snake: participant=%d jury=%d",
              participant.length, jury.length);
    }

    quitf(_ok, "valid snake of length %d", participant.length);
}

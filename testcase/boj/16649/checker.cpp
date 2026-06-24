#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;

struct Answer {
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    int m = stream.readInt(-1, 100, "m");
    stream.readEoln();

    if (m == -1) {
        stream.readEof();
        return {true};
    }
    if (m == 0) {
        stream.quitf(_wa, "m must be -1 or between 1 and 100");
    }

    vector<string> grid(m);
    int cubes = 0;
    for (int row = 0; row < m; ++row) {
        grid[row] = stream.readToken(format("[o.]{%d}", m), format("row[%d]", row + 1).c_str());
        stream.readEoln();
        for (char cell : grid[row]) {
            if (cell == 'o') {
                ++cubes;
            }
        }
    }
    stream.readEof();

    if (cubes != n) {
        stream.quitf(_wa, "expected exactly %d cubes, found %d", n, cubes);
    }
    if (grid[m - 1][0] != 'o') {
        stream.quitf(_wa, "bottom-left cell must contain a cube");
    }

    auto occupied = [&](int x, int y) {
        return grid[m - 1 - y][x] == 'o';
    };

    for (int x = 0; x < m; ++x) {
        for (int y = 0; y < m; ++y) {
            if (!occupied(x, y)) {
                continue;
            }
            if (x > 0 && !occupied(x - 1, y)) {
                stream.quitf(_wa, "cell (%d, %d) has a gap to its left", x + 1, y + 1);
            }
            if (y > 0 && !occupied(x, y - 1)) {
                stream.quitf(_wa, "cell (%d, %d) has a gap below it", x + 1, y + 1);
            }
            if (!occupied(y, x)) {
                stream.quitf(_wa, "cell (%d, %d) is not symmetric", x + 1, y + 1);
            }
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100, "n");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid symmetric stair while jury claims impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid symmetric stair but participant claims impossible");
    }

    quitf(_ok, "valid symmetric stair with %d cubes", n);
}

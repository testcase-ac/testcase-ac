#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

int n, m;
vector<vector<int>> grid;

struct Answer {
    int length;
};

Answer readAnswer(InStream& stream) {
    int maxLength = 2 * (n + m);
    int k = stream.readInt(1, maxLength, "K");
    stream.readEoln();

    long long pathXor = 0;
    int prevY = -1;
    int prevX = -1;

    for (int i = 0; i < k; ++i) {
        int y = stream.readInt(0, n - 1, format("y[%d]", i + 1).c_str());
        stream.readSpace();
        int x = stream.readInt(0, m - 1, format("x[%d]", i + 1).c_str());
        stream.readEoln();

        if (i == 0) {
            if (y != 0 || x != 0) {
                stream.quitf(_wa, "path starts at (%d, %d) instead of (0, 0)", y, x);
            }
        } else {
            int dy = abs(y - prevY);
            int dx = abs(x - prevX);
            if (dy > 1 || dx > 1 || (dy == 0 && dx == 0)) {
                stream.quitf(_wa,
                             "step %d moves from (%d, %d) to (%d, %d), which is not 8-neighbor adjacent",
                             i + 1,
                             prevY,
                             prevX,
                             y,
                             x);
            }
        }

        if (i + 1 == k && (y != n - 1 || x != m - 1)) {
            stream.quitf(_wa,
                         "path ends at (%d, %d) instead of (%d, %d)",
                         y,
                         x,
                         n - 1,
                         m - 1);
        }

        pathXor ^= grid[y][x];
        prevY = y;
        prevX = x;
    }

    if (pathXor != 0) {
        stream.quitf(_wa, "path xor is %lld instead of 0", pathXor);
    }

    stream.readEof();
    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    grid.assign(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            grid[i][j] = inf.readInt();
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok,
          "valid path with K=%d, jury K=%d",
          participant.length,
          jury.length);
}

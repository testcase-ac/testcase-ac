#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int n;
vector<string> inputGrid;

struct Claim {
    int bombCount;
};

Claim readClaim(InStream& stream) {
    vector<string> output(n);
    int bombCount = 0;

    for (int i = 0; i < n; ++i) {
        output[i] = stream.readToken("[.OXB]{1,2000}", format("row[%d]", i + 1).c_str());
        if ((int)output[i].size() != n) {
            stream.quitf(_wa, "row %d has length %d, expected %d", i + 1,
                         (int)output[i].size(), n);
        }
        stream.readEoln();

        for (int j = 0; j < n; ++j) {
            if (inputGrid[i][j] == '.') {
                if (output[i][j] != '.' && output[i][j] != 'B') {
                    stream.quitf(_wa,
                                 "row %d column %d is '%c', expected '.' or 'B' on an empty cell",
                                 i + 1, j + 1, output[i][j]);
                }
                if (output[i][j] == 'B') {
                    ++bombCount;
                }
            } else if (output[i][j] != inputGrid[i][j]) {
                stream.quitf(_wa, "row %d column %d is '%c', expected original '%c'",
                             i + 1, j + 1, output[i][j], inputGrid[i][j]);
            }
        }
    }
    stream.readEof();

    vector<vector<char>> destroyed(n, vector<char>(n, 0));
    const int di[4] = {-1, 1, 0, 0};
    const int dj[4] = {0, 0, -1, 1};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (output[i][j] != 'B') {
                continue;
            }

            for (int dir = 0; dir < 4; ++dir) {
                int ni = i + di[dir];
                int nj = j + dj[dir];
                while (0 <= ni && ni < n && 0 <= nj && nj < n &&
                       inputGrid[ni][nj] == '.') {
                    ni += di[dir];
                    nj += dj[dir];
                }

                if (0 <= ni && ni < n && 0 <= nj && nj < n) {
                    if (inputGrid[ni][nj] == 'O') {
                        stream.quitf(_wa,
                                     "bomb at row %d column %d destroys building at row %d column %d",
                                     i + 1, j + 1, ni + 1, nj + 1);
                    }
                    destroyed[ni][nj] = 1;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (inputGrid[i][j] == 'X' && !destroyed[i][j]) {
                stream.quitf(_wa, "rubble at row %d column %d is not reached by any bomb",
                             i + 1, j + 1);
            }
        }
    }

    return {bombCount};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    inputGrid.resize(n);
    for (int i = 0; i < n; ++i) {
        inputGrid[i] = inf.readToken();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    quitf(_ok, "valid reconstruction with %d bombs; jury used %d bombs",
          participant.bombCount, jury.bombCount);
}

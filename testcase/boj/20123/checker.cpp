#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;

struct Answer {
    bool impossible;
};

bool inside(int r, int c) {
    return 0 <= r && r < n && 0 <= c && c <= r;
}

Answer readAnswer(InStream& stream) {
    string first = stream.readToken();

    if (first == "impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible");
        }
        return {true};
    }

    vector<string> grid(n);
    grid[0] = first;
    for (int i = 1; i < n; ++i) {
        grid[i] = stream.readToken();
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after staircase");
    }

    for (int r = 0; r < n; ++r) {
        if ((int)grid[r].size() != r + 1) {
            stream.quitf(_wa, "row %d has length %d, expected %d",
                         r + 1, (int)grid[r].size(), r + 1);
        }
        for (int c = 0; c <= r; ++c) {
            char ch = grid[r][c];
            if (ch != 'b' && ch != 'p' && ch != 'q' && ch != 'd' &&
                ch != '-' && ch != '|') {
                stream.quitf(_wa, "invalid character '%c' at row %d column %d",
                             ch, r + 1, c + 1);
            }
        }
    }

    vector<vector<int>> armUse(n);
    for (int r = 0; r < n; ++r) {
        armUse[r].assign(r + 1, 0);
    }

    auto requireArm = [&](int r, int c, char expected, int pivotR, int pivotC) {
        if (!inside(r, c)) {
            stream.quitf(_wa, "tromino at row %d column %d points outside the staircase",
                         pivotR + 1, pivotC + 1);
        }
        if (grid[r][c] != expected) {
            stream.quitf(_wa,
                         "tromino at row %d column %d expects '%c' at row %d column %d, found '%c'",
                         pivotR + 1, pivotC + 1, expected, r + 1, c + 1, grid[r][c]);
        }
        ++armUse[r][c];
    };

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c <= r; ++c) {
            char ch = grid[r][c];
            if (ch == 'b') {
                requireArm(r, c + 1, '-', r, c);
                requireArm(r - 1, c, '|', r, c);
            } else if (ch == 'p') {
                requireArm(r, c + 1, '-', r, c);
                requireArm(r + 1, c, '|', r, c);
            } else if (ch == 'q') {
                requireArm(r, c - 1, '-', r, c);
                requireArm(r + 1, c, '|', r, c);
            } else if (ch == 'd') {
                requireArm(r, c - 1, '-', r, c);
                requireArm(r - 1, c, '|', r, c);
            }
        }
    }

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c <= r; ++c) {
            char ch = grid[r][c];
            if (ch == '-' || ch == '|') {
                if (armUse[r][c] == 0) {
                    stream.quitf(_wa, "'%c' at row %d column %d is not part of a tromino",
                                 ch, r + 1, c + 1);
                }
                if (armUse[r][c] > 1) {
                    stream.quitf(_wa, "'%c' at row %d column %d belongs to %d trominoes",
                                 ch, r + 1, c + 1, armUse[r][c]);
                }
            }
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000, "N");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid tiling while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible, but jury has a valid tiling");
    }

    quitf(_ok, "valid tiling");
}

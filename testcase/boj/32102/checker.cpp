#include "testlib.h"

#include <array>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

int n, m;
long long needR, needG, needB;

struct Answer {
    bool possible;
};

int colorIndex(char ch) {
    if (ch == 'R') return 0;
    if (ch == 'G') return 1;
    if (ch == 'B') return 2;
    return -1;
}

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("[A-Za-z]+", "verdict");
    for (char& ch : verdict) ch = char(toupper(ch));

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false};
    }
    if (verdict != "YES") {
        stream.quitf(_wa, "verdict must be YES or NO, found '%s'", verdict.c_str());
    }

    vector<string> grid(n);
    array<long long, 3> counts = {0, 0, 0};
    for (int i = 0; i < n; ++i) {
        grid[i] = stream.readToken(format("[RGB]{%d}", m), format("row[%d]", i + 1).c_str());
        for (int j = 0; j < m; ++j) {
            int idx = colorIndex(grid[i][j]);
            counts[idx]++;
            if (i > 0 && grid[i - 1][j] == grid[i][j]) {
                stream.quitf(_wa, "adjacent cells (%d,%d) and (%d,%d) both have color %c",
                             i, j + 1, i + 1, j + 1, grid[i][j]);
            }
            if (j > 0 && grid[i][j - 1] == grid[i][j]) {
                stream.quitf(_wa, "adjacent cells (%d,%d) and (%d,%d) both have color %c",
                             i + 1, j, i + 1, j + 1, grid[i][j]);
            }
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after grid");
    }

    if (counts[0] != needR || counts[1] != needG || counts[2] != needB) {
        stream.quitf(_wa, "color counts differ: expected R=%lld G=%lld B=%lld, found R=%lld G=%lld B=%lld",
                     needR, needG, needB, counts[0], counts[1], counts[2]);
    }
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    needR = inf.readLong();
    needG = inf.readLong();
    needB = inf.readLong();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.possible == participant.possible) {
        quitf(_ok, "%s", participant.possible ? "valid coloring" : "impossible");
    }
    if (jury.possible) {
        quitf(_wa, "jury has a valid coloring, but participant answered NO");
    }
    quitf(_fail, "participant found a valid coloring while jury answered NO");
}

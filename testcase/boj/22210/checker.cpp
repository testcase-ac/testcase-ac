#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int h, w;
vector<string> target;

vector<string> readGrid(InStream& stream, TResult invalidVerdict, const char* owner) {
    vector<string> grid(h);
    const string pattern = "[X.]{" + to_string(w) + "}";

    for (int i = 0; i < h; ++i) {
        grid[i] = stream.readToken(pattern, format("%s row %d", owner, i + 1).c_str());
        stream.readEoln();
    }
    stream.readEof();

    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            int mines = 0;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    int nr = r + dr;
                    int nc = c + dc;
                    if (0 <= nr && nr < h && 0 <= nc && nc < w && grid[nr][nc] == 'X') {
                        ++mines;
                    }
                }
            }
            int expected = target[r][c] - '0';
            if (mines != expected) {
                stream.quitf(invalidVerdict,
                             "%s grid gives count %d at cell (%d, %d), expected %d",
                             owner, mines, r + 1, c + 1, expected);
            }
        }
    }

    return grid;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    h = inf.readInt();
    w = inf.readInt();
    target.resize(h);
    for (int i = 0; i < h; ++i) {
        target[i] = inf.readToken();
    }

    readGrid(ans, _fail, "jury");
    readGrid(ouf, _wa, "participant");

    quitf(_ok, "participant grid matches all mine counts");
}

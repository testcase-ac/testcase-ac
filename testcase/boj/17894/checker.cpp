#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n, m;
vector<string> grid;

const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, 1, 0, -1};

bool inside(int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < m;
}

void readAndValidateAnswer(InStream& stream) {
    vector<string> answer(n);
    for (int r = 0; r < n; ++r) {
        answer[r] = stream.readToken(format("[.#E]{%d}", m), format("row[%d]", r + 1).c_str());
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after grid");
    }

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] == '#') {
                if (answer[r][c] != '#') {
                    stream.quitf(_wa, "water cell (%d, %d) is changed to '%c'", r + 1, c + 1, answer[r][c]);
                }
            } else if (answer[r][c] == '#') {
                stream.quitf(_wa, "land cell (%d, %d) is changed to water", r + 1, c + 1);
            }
        }
    }

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (answer[r][c] != 'E') {
                continue;
            }
            for (int dir = 0; dir < 4; ++dir) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                if (inside(nr, nc) && answer[nr][nc] == 'E') {
                    stream.quitf(_wa, "coffee shops at (%d, %d) and (%d, %d) are adjacent",
                                 r + 1, c + 1, nr + 1, nc + 1);
                }
            }
        }
    }

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] == '#') {
                continue;
            }

            bool covered = answer[r][c] == 'E';
            for (int dir = 0; dir < 4 && !covered; ++dir) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                covered = inside(nr, nc) && answer[nr][nc] == 'E';
            }
            if (!covered) {
                stream.quitf(_wa, "land cell (%d, %d) is not covered by a coffee shop", r + 1, c + 1);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100, "n");
    m = inf.readInt(1, 100, "m");
    grid.resize(n);
    for (int r = 0; r < n; ++r) {
        grid[r] = inf.readToken(format("[.#]{%d}", m), format("map row[%d]", r + 1).c_str());
    }

    readAndValidateAnswer(ans);
    readAndValidateAnswer(ouf);

    quitf(_ok, "valid placement");
}

#include "testlib.h"

#include <queue>
#include <string>
#include <vector>

using namespace std;

int h, w;
long long targetComponents;

struct Answer {
    bool impossible;
    long long components;
};

long long countComponents(const vector<string>& grid) {
    vector<vector<int>> seen(h, vector<int>(w, 0));
    long long components = 0;

    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};

    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            if (grid[r][c] != '.' || seen[r][c]) {
                continue;
            }

            ++components;
            queue<pair<int, int>> q;
            q.push({r, c});
            seen[r][c] = 1;

            while (!q.empty()) {
                int cr = q.front().first;
                int cc = q.front().second;
                q.pop();

                for (int dir = 0; dir < 4; ++dir) {
                    int nr = cr + dr[dir];
                    int nc = cc + dc[dir];
                    if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
                        continue;
                    }
                    if (grid[nr][nc] != '.' || seen[nr][nc]) {
                        continue;
                    }
                    seen[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    return components;
}

Answer readAnswer(InStream& stream) {
    string rowPattern = format("[.#]{%d}", w);
    string first = stream.readToken(format("Impossible|%s", rowPattern.c_str()), "answer");
    stream.readEoln();

    if (first == "Impossible") {
        stream.readEof();
        return {true, 0};
    }

    vector<string> grid(h);
    grid[0] = first;
    for (int r = 1; r < h; ++r) {
        grid[r] = stream.readToken(rowPattern, format("grid row %d", r + 1).c_str());
        stream.readEoln();
    }
    stream.readEof();

    long long components = countComponents(grid);
    if (components != targetComponents) {
        stream.quitf(_wa,
                     "grid has %lld dry-land components, expected %lld",
                     components,
                     targetComponents);
    }

    return {false, components};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    h = inf.readInt();
    w = inf.readInt();
    targetComponents = inf.readLong();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid grid while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible, but jury has a valid grid");
    }

    quitf(_ok, "valid grid with %lld dry-land components", participant.components);
}

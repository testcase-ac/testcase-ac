#include "testlib.h"

#include <queue>
#include <string>
#include <vector>

using namespace std;

int n, m;

struct Answer {
    bool exists;
};

bool inRange(int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < m;
}

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("[A-Za-z]+", "answer verdict");
    if (verdict == "NO") {
        stream.readEoln();
        stream.readEof();
        return {false};
    }
    if (verdict != "YES") {
        stream.quitf(_wa, "expected YES or NO, found '%s'", verdict.c_str());
    }
    stream.readEoln();

    vector<string> grid(n);
    int selected = 0;
    for (int i = 0; i < n; ++i) {
        grid[i] = stream.readToken(format("[01]{%d}", m), format("row[%d]", i + 1));
        stream.readEoln();
        for (char ch : grid[i]) {
            selected += ch == '1';
        }
    }
    stream.readEof();

    if (2LL * selected > 1LL * n * m) {
        stream.quitf(_wa, "selected %d cells, more than floor(n*m/2)=%lld", selected, 1LL * n * m / 2);
    }
    if (selected == 0) {
        stream.quitf(_wa, "selected set is empty");
    }

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] == '1') {
                continue;
            }
            bool dominated = false;
            for (int dir = 0; dir < 4; ++dir) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                if (inRange(nr, nc) && grid[nr][nc] == '1') {
                    dominated = true;
                }
            }
            if (!dominated) {
                stream.quitf(_wa, "cell (%d, %d) is not dominated", r + 1, c + 1);
            }
        }
    }

    vector<vector<char>> seen(n, vector<char>(m, 0));
    queue<pair<int, int>> q;
    for (int r = 0; r < n && q.empty(); ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] == '1') {
                seen[r][c] = 1;
                q.push({r, c});
                break;
            }
        }
    }

    int reached = 0;
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        ++reached;
        for (int dir = 0; dir < 4; ++dir) {
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            if (inRange(nr, nc) && !seen[nr][nc] && grid[nr][nc] == '1') {
                seen[nr][nc] = 1;
                q.push({nr, nc});
            }
        }
    }

    if (reached != selected) {
        stream.quitf(_wa, "selected cells are not connected: reached %d of %d", reached, selected);
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 1000, "n");
    m = inf.readInt(2, 1000, "m");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.exists && participant.exists) {
        quitf(_fail, "participant found a valid connected dominating set while jury answered NO");
    }
    if (jury.exists && !participant.exists) {
        quitf(_wa, "jury has a valid connected dominating set, participant answered NO");
    }

    quitf(_ok, "valid feasibility claim");
}

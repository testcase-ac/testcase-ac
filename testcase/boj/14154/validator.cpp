#include "testlib.h"

#include <array>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int t = inf.readInt(1, 1000000, "T");
    (void)t;
    inf.readEoln();

    vector<string> board(n);
    vector<vector<pair<int, int>>> cells(26);
    array<int, 26> heads{};

    for (int i = 0; i < n; ++i) {
        board[i] = inf.readToken("[.#A-Za-z]{" + to_string(n) + "}", "row");
        inf.readEoln();

        for (int j = 0; j < n; ++j) {
            char c = board[i][j];
            if ('A' <= c && c <= 'Z') {
                int id = c - 'A';
                ++heads[id];
                cells[id].push_back({i, j});
            } else if ('a' <= c && c <= 'z') {
                cells[c - 'a'].push_back({i, j});
            }
        }
    }

    const int di[4] = {-1, 0, 1, 0};
    const int dj[4] = {0, 1, 0, -1};

    auto sameSnake = [&](int r, int c, int id) {
        if (r < 0 || r >= n || c < 0 || c >= n) {
            return false;
        }
        char ch = board[r][c];
        return ch == char('A' + id) || ch == char('a' + id);
    };

    for (int id = 0; id < 26; ++id) {
        if (cells[id].empty()) {
            continue;
        }

        ensuref(heads[id] == 1, "snake %c must have exactly one head, found %d",
                char('A' + id), heads[id]);
        ensuref(cells[id].size() >= 2, "snake %c has length %d, expected at least 2",
                char('A' + id), int(cells[id].size()));

        int endpointCount = 0;
        bool headIsEndpoint = false;
        for (auto [r, c] : cells[id]) {
            int degree = 0;
            for (int dir = 0; dir < 4; ++dir) {
                degree += sameSnake(r + di[dir], c + dj[dir], id);
            }

            bool isHead = board[r][c] == char('A' + id);
            if (degree == 1) {
                ++endpointCount;
                headIsEndpoint = headIsEndpoint || isHead;
            } else {
                ensuref(degree == 2, "snake %c cell (%d,%d) has degree %d",
                        char('A' + id), r + 1, c + 1, degree);
                ensuref(!isHead, "snake %c head at (%d,%d) is not an endpoint",
                        char('A' + id), r + 1, c + 1);
            }
        }

        ensuref(endpointCount == 2, "snake %c has %d endpoints, expected 2",
                char('A' + id), endpointCount);
        ensuref(headIsEndpoint, "snake %c head must be one of the endpoints",
                char('A' + id));

        vector<vector<bool>> seen(n, vector<bool>(n, false));
        queue<pair<int, int>> q;
        q.push(cells[id][0]);
        seen[cells[id][0].first][cells[id][0].second] = true;

        int visited = 0;
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            ++visited;

            for (int dir = 0; dir < 4; ++dir) {
                int nr = r + di[dir];
                int nc = c + dj[dir];
                if (sameSnake(nr, nc, id) && !seen[nr][nc]) {
                    seen[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }

        ensuref(visited == int(cells[id].size()),
                "snake %c cells must form one connected component", char('A' + id));
    }

    inf.readEof();
}

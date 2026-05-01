#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

bool validMaze(const vector<string>& g) {
    int N = (int)g.size();
    if (N == 0) return false;
    int M = (int)g[0].size();
    int hR = -1, hC = -1;
    int cntH = 0, cntP = 0, cntE = 0;

    for (int i = 0; i < N; ++i) {
        if ((int)g[i].size() != M) return false;
        for (int j = 0; j < M; ++j) {
            char ch = g[i][j];
            if (ch == 'H') {
                cntH++;
                hR = i; hC = j;
            } else if (ch == 'P') {
                cntP++;
            } else if (ch == '#') {
                cntE++;
            }
        }
    }

    if (cntH != 1) return false;
    if (cntP < 1) return false;
    if (cntE < 1) return false;

    // BFS from H to see if some exit is reachable
    vector<vector<int>> dist(N, vector<int>(M, -1));
    queue<pair<int,int>> q;
    dist[hR][hC] = 0;
    q.push({hR, hC});

    int dr[4] = { -1, 1, 0, 0 };
    int dc[4] = { 0, 0, -1, 1 };

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
            if (g[nr][nc] == 'X') continue; // wall
            if (dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc});
        }
    }

    bool anyReach = false;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (g[i][j] == '#' && dist[i][j] != -1)
                anyReach = true;

    return anyReach;
}

vector<string> genRandomRect(int minN, int maxN, int minM, int maxM, double wallLo, double wallHi) {
    while (true) {
        int N = rnd.next(minN, maxN);
        int M = rnd.next(minM, maxM);
        if (1LL * N * M < 4) continue; // need enough cells
        if (1LL * N * M > 400) continue; // keep input compact

        vector<string> g(N, string(M, '.'));

        double density = wallLo + (wallHi - wallLo) * rnd.next(); // in [wallLo, wallHi)
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (rnd.next() < density) g[i][j] = 'X';
            }
        }

        vector<pair<int,int>> empties;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (g[i][j] == '.')
                    empties.push_back({i, j});

        if ((int)empties.size() < 3) continue; // need H, at least one #, at least one P

        shuffle(empties.begin(), empties.end());

        auto [hR, hC] = empties[0];
        g[hR][hC] = 'H';

        int rest = (int)empties.size() - 1; // remaining free cells
        if (rest < 2) continue; // need space for exit(s) and P(s)

        int maxExit = min(5, rest - 1); // leave space for at least 1 P
        maxExit = min(maxExit, 100);    // respect max 100 exits
        if (maxExit < 1) continue;
        int exitCount = rnd.next(1, maxExit);

        int remaining = rest - exitCount;
        int maxP = min(8, remaining);
        maxP = min(maxP, 100);          // respect max 100 people
        if (maxP < 1) continue;
        int pCount = rnd.next(1, maxP);

        // place exits
        for (int i = 0; i < exitCount; ++i) {
            auto [r, c] = empties[1 + i];
            g[r][c] = '#';
        }

        // place people
        for (int i = 0; i < pCount; ++i) {
            auto [r, c] = empties[1 + exitCount + i];
            g[r][c] = 'P';
        }

        if (validMaze(g)) return g;
    }
}

vector<string> genCorridor() {
    while (true) {
        int len = rnd.next(4, 20);
        bool horizontal = (rnd.next(0, 1) == 1);

        vector<char> line(len, '.');

        int posH = rnd.next(0, len - 1);
        line[posH] = 'H';

        int maxExits = min(3, len - 1);
        int exitCount = rnd.next(1, maxExits);

        vector<int> positions;
        for (int i = 0; i < len; ++i)
            if (i != posH)
                positions.push_back(i);
        shuffle(positions.begin(), positions.end());

        vector<int> exitPos(exitCount);
        for (int i = 0; i < exitCount; ++i) {
            exitPos[i] = positions[i];
            line[positions[i]] = '#';
        }

        int chosenIdx = rnd.next(0, exitCount - 1);
        int ex = exitPos[chosenIdx];
        int L = min(posH, ex);
        int R = max(posH, ex);

        // Candidates for walls: outside the guaranteed free segment [L, R]
        vector<int> wallCand;
        for (int i = 0; i < len; ++i) {
            if (line[i] == '.' && !(L <= i && i <= R)) {
                wallCand.push_back(i);
            }
        }

        int maxWalls = (int)wallCand.size();
        int wallCount = maxWalls > 0 ? rnd.next(0, maxWalls) : 0;
        shuffle(wallCand.begin(), wallCand.end());
        for (int i = 0; i < wallCount; ++i) {
            line[wallCand[i]] = 'X';
        }

        vector<int> freeForP;
        for (int i = 0; i < len; ++i)
            if (line[i] == '.')
                freeForP.push_back(i);

        if (freeForP.empty()) continue;

        int maxP = min(5, (int)freeForP.size());
        int pCount = rnd.next(1, maxP);
        shuffle(freeForP.begin(), freeForP.end());
        for (int i = 0; i < pCount; ++i) {
            line[freeForP[i]] = 'P';
        }

        vector<string> g;
        if (horizontal) {
            g.assign(1, string(len, '.'));
            for (int i = 0; i < len; ++i) g[0][i] = line[i];
        } else {
            g.assign(len, string(1, '.'));
            for (int i = 0; i < len; ++i) g[i][0] = line[i];
        }

        if (validMaze(g)) return g;
    }
}

vector<string> genPlusMaze() {
    while (true) {
        int k = rnd.next(2, 4); // size 5,7,9
        int size = 2 * k + 1;
        int N = size, M = size;
        vector<string> g(N, string(M, 'X'));
        int mid = N / 2;

        // Carve plus shape
        for (int c = 0; c < M; ++c) g[mid][c] = '.';
        for (int r = 0; r < N; ++r) g[r][mid] = '.';

        // Optional side rooms off the arms
        for (int r = 0; r < N; ++r) {
            if (r == mid) continue;
            if (g[r][mid] == '.') {
                if (mid - 1 >= 0 && rnd.next(0, 1)) g[r][mid - 1] = '.';
                if (mid + 1 < M && rnd.next(0, 1)) g[r][mid + 1] = '.';
            }
        }
        for (int c = 0; c < M; ++c) {
            if (c == mid) continue;
            if (g[mid][c] == '.') {
                if (mid - 1 >= 0 && rnd.next(0, 1)) g[mid - 1][c] = '.';
                if (mid + 1 < N && rnd.next(0, 1)) g[mid + 1][c] = '.';
            }
        }

        // Place H at center
        g[mid][mid] = 'H';

        // Possible exit endpoints
        vector<pair<int,int>> endpoints;
        endpoints.push_back({mid, 0});
        endpoints.push_back({mid, M - 1});
        endpoints.push_back({0, mid});
        endpoints.push_back({N - 1, mid});

        shuffle(endpoints.begin(), endpoints.end());
        int exitCount = rnd.next(1, 4);
        for (int i = 0; i < exitCount; ++i) {
            int r = endpoints[i].first;
            int c = endpoints[i].second;
            g[r][c] = '#';
        }

        vector<pair<int,int>> cells;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (g[i][j] == '.')
                    cells.push_back({i, j});

        if (cells.empty()) continue;

        int maxP = min(10, (int)cells.size());
        int pCount = rnd.next(1, maxP);
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < pCount; ++i) {
            auto [r, c] = cells[i];
            g[r][c] = 'P';
        }

        if (validMaze(g)) return g;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3); // 0: small random, 1: corridor, 2: plus, 3: larger random
    vector<string> grid;

    if (mode == 0) {
        grid = genRandomRect(2, 8, 2, 8, 0.0, 0.4);
    } else if (mode == 1) {
        grid = genCorridor();
    } else if (mode == 2) {
        grid = genPlusMaze();
    } else {
        grid = genRandomRect(7, 20, 7, 20, 0.2, 0.6);
    }

    int N = (int)grid.size();
    int M = (int)grid[0].size();

    println(N, M);
    for (int i = 0; i < N; ++i)
        println(grid[i]);

    return 0;
}

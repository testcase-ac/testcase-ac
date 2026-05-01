#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 4); // 0: straight, 1: single bend, 2-4: random walk
    int N;
    vector<string> g;

    if (scenario == 0) {
        // Scenario 0: Straight line between doors (0 mirrors possible)
        N = rnd.next(2, 15);
        g.assign(N, string(N, '.'));

        bool horizontal = (rnd.next(0, 1) == 0);
        vector<pair<int,int>> pathCells;

        if (horizontal) {
            int r = rnd.next(0, N - 1);
            int c1 = rnd.next(0, N - 1);
            int c2 = rnd.next(0, N - 1);
            while (c2 == c1) c2 = rnd.next(0, N - 1);
            if (c1 > c2) swap(c1, c2);

            for (int c = c1; c <= c2; ++c) pathCells.push_back({r, c});

            g[r][c1] = '#';
            g[r][c2] = '#';
            for (int c = c1 + 1; c <= c2 - 1; ++c) {
                bool mirror = (rnd.next(0, 4) == 0); // 20% chance
                g[r][c] = mirror ? '!' : '.';
            }
        } else {
            int c = rnd.next(0, N - 1);
            int r1 = rnd.next(0, N - 1);
            int r2 = rnd.next(0, N - 1);
            while (r2 == r1) r2 = rnd.next(0, N - 1);
            if (r1 > r2) swap(r1, r2);

            for (int r = r1; r <= r2; ++r) pathCells.push_back({r, c});

            g[r1][c] = '#';
            g[r2][c] = '#';
            for (int r = r1 + 1; r <= r2 - 1; ++r) {
                bool mirror = (rnd.next(0, 4) == 0); // 20% chance
                g[r][c] = mirror ? '!' : '.';
            }
        }

        vector<vector<bool>> isPath(N, vector<bool>(N, false));
        for (auto &p : pathCells) isPath[p.first][p.second] = true;

        int densityType = rnd.next(0, 2);
        double pWall, pMirror;
        if (densityType == 0) { pWall = 0.10; pMirror = 0.20; }
        else if (densityType == 1) { pWall = 0.30; pMirror = 0.30; }
        else { pWall = 0.50; pMirror = 0.20; }

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (isPath[r][c]) continue;
                double t = rnd.next(0.0, 1.0);
                if (t < pWall) g[r][c] = '*';
                else if (t < pWall + pMirror) g[r][c] = '!';
                else g[r][c] = '.';
            }
        }
    } else if (scenario == 1) {
        // Scenario 1: Door1 - mid - Door2 with single bend at mid (requires 1 mirror on this path)
        N = rnd.next(3, 15);
        g.assign(N, string(N, '.'));

        int rm = rnd.next(0, N - 1);
        int cm = rnd.next(0, N - 1);

        int c1;
        do { c1 = rnd.next(0, N - 1); } while (c1 == cm);
        int r2;
        do { r2 = rnd.next(0, N - 1); } while (r2 == rm);

        pair<int,int> door1 = {rm, c1};
        pair<int,int> mid   = {rm, cm};
        pair<int,int> door2 = {r2, cm};

        vector<pair<int,int>> path;
        int r = door1.first, c = door1.second;
        path.push_back(door1);

        int dc = (cm > c ? 1 : -1);
        while (c != cm) {
            c += dc;
            path.push_back({r, c});
        }
        int dr = (r2 > r ? 1 : -1);
        while (r != r2) {
            r += dr;
            path.push_back({r, c});
        }

        int k = (int)path.size();
        vector<vector<bool>> isPath(N, vector<bool>(N, false));
        for (auto &p : path) isPath[p.first][p.second] = true;

        for (int i = 0; i < k; ++i) {
            int pr = path[i].first, pc = path[i].second;
            if (i == 0 || i == k - 1) {
                g[pr][pc] = '#';
            } else if (pr == mid.first && pc == mid.second) {
                g[pr][pc] = '!';
            } else {
                bool mirror = (rnd.next(0, 3) == 0); // 25%
                g[pr][pc] = mirror ? '!' : '.';
            }
        }

        int densityType = rnd.next(0, 2);
        double pWall, pMirror;
        if (densityType == 0) { pWall = 0.15; pMirror = 0.25; }
        else if (densityType == 1) { pWall = 0.35; pMirror = 0.35; }
        else { pWall = 0.55; pMirror = 0.20; }

        for (int rr = 0; rr < N; ++rr) {
            for (int cc = 0; cc < N; ++cc) {
                if (isPath[rr][cc]) continue;
                double t = rnd.next(0.0, 1.0);
                if (t < pWall) g[rr][cc] = '*';
                else if (t < pWall + pMirror) g[rr][cc] = '!';
                else g[rr][cc] = '.';
            }
        }
    } else {
        // Scenario 2+: Random self-avoiding walk with multiple bends
        N = rnd.next(5, 15);
        g.assign(N, string(N, '.'));

        bool wantManyBends = (rnd.next(0, 1) == 0);
        vector<pair<int,int>> path;
        int attempts = 0;

        while (true) {
            ++attempts;
            int r0 = rnd.next(0, N - 1);
            int c0 = rnd.next(0, N - 1);

            vector<vector<bool>> used(N, vector<bool>(N, false));
            path.clear();
            path.push_back({r0, c0});
            used[r0][c0] = true;

            int maxLen = min(N * N / 2, 3 * N);
            if (maxLen < 2) maxLen = 2;
            int targetLen = rnd.next(2, maxLen);

            int r = r0, c = c0;
            for (int step = 1; step < targetLen; ++step) {
                vector<pair<int,int>> neigh;
                static const int dr[4] = {-1, 1, 0, 0};
                static const int dc[4] = {0, 0, -1, 1};
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (0 <= nr && nr < N && 0 <= nc && nc < N && !used[nr][nc]) {
                        neigh.push_back({nr, nc});
                    }
                }
                if (neigh.empty()) break;
                auto nxt = rnd.any(neigh);
                r = nxt.first; c = nxt.second;
                path.push_back(nxt);
                used[r][c] = true;
            }

            if ((int)path.size() >= 2) {
                int bends = 0;
                for (int i = 1; i + 1 < (int)path.size(); ++i) {
                    int r0p = path[i-1].first, c0p = path[i-1].second;
                    int r1p = path[i].first,   c1p = path[i].second;
                    int r2p = path[i+1].first, c2p = path[i+1].second;
                    int dr1 = r1p - r0p, dc1 = c1p - c0p;
                    int dr2 = r2p - r1p, dc2 = c2p - c1p;
                    if (dr1 != dr2 || dc1 != dc2) ++bends;
                }
                if (!wantManyBends || bends >= 2 || attempts > 100) break;
            }
            if (attempts > 300) break; // fallback, accept whatever
        }

        int k = (int)path.size();
        vector<vector<bool>> isPath(N, vector<bool>(N, false));
        for (auto &p : path) isPath[p.first][p.second] = true;

        for (int i = 0; i < k; ++i) {
            int pr = path[i].first, pc = path[i].second;
            if (i == 0 || i == k - 1) {
                g[pr][pc] = '#';
            } else {
                // Determine if this is a bend
                bool bend = false;
                if (i > 0 && i + 1 < k) {
                    int r0p = path[i-1].first, c0p = path[i-1].second;
                    int r1p = path[i].first,   c1p = path[i].second;
                    int r2p = path[i+1].first, c2p = path[i+1].second;
                    int dr1 = r1p - r0p, dc1 = c1p - c0p;
                    int dr2 = r2p - r1p, dc2 = c2p - c1p;
                    if (dr1 != dr2 || dc1 != dc2) bend = true;
                }
                if (bend) {
                    g[pr][pc] = '!';
                } else {
                    bool mirror = (rnd.next(0, 3) == 0); // 25%
                    g[pr][pc] = mirror ? '!' : '.';
                }
            }
        }

        int densityType = rnd.next(0, 2);
        double pWall, pMirror;
        if (densityType == 0) { pWall = 0.20; pMirror = 0.30; }
        else if (densityType == 1) { pWall = 0.40; pMirror = 0.35; }
        else { pWall = 0.60; pMirror = 0.25; }

        for (int rr = 0; rr < N; ++rr) {
            for (int cc = 0; cc < N; ++cc) {
                if (isPath[rr][cc]) continue;
                double t = rnd.next(0.0, 1.0);
                if (t < pWall) g[rr][cc] = '*';
                else if (t < pWall + pMirror) g[rr][cc] = '!';
                else g[rr][cc] = '.';
            }
        }
    }

    println(N);
    for (int i = 0; i < N; ++i) println(g[i]);

    return 0;
}

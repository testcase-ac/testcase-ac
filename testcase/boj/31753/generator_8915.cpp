#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = 0, M = 0;
    vector<string> g;

    int pattern = rnd.next(0, 8);

    switch (pattern) {
        case 0: {
            // Sample 1 shape
            N = 3; M = 3;
            g = {
                "#.#",
                "...",
                "#.#"
            };
            break;
        }
        case 1: {
            // Sample 2 shape
            N = 3; M = 3;
            g = {
                "..#",
                "...",
                "..."
            };
            break;
        }
        case 2: {
            // Sample 3 shape
            N = 1; M = 4;
            g = {
                "...#"
            };
            break;
        }
        case 3: {
            // Small random grid with varying obstacle density
            N = rnd.next(1, 6);
            M = rnd.next(1, 6);
            g.assign(N, string(M, '.'));
            vector<int> probs = {0, 20, 40, 60, 80};
            int p = rnd.any(probs); // probability (percent) of '#'
            int emptyCount = N * M;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if (rnd.next(0, 99) < p) {
                        g[i][j] = '#';
                        --emptyCount;
                    }
                }
            }
            if (emptyCount == 0) {
                int ri = rnd.next(0, N - 1);
                int rj = rnd.next(0, M - 1);
                g[ri][rj] = '.';
            }
            break;
        }
        case 4: {
            // Pure path: single row or single column of empties
            int L = rnd.next(1, 12);
            bool horizontal = rnd.next(0, 1);
            if (horizontal) {
                N = 1; M = L;
            } else {
                N = L; M = 1;
            }
            g.assign(N, string(M, '.'));
            break;
        }
        case 5: {
            // Ring/cycle: border empty, inside blocked
            int S = rnd.next(4, 6);
            N = M = S;
            g.assign(N, string(M, '#'));
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if (i == 0 || i == N - 1 || j == 0 || j == M - 1) {
                        g[i][j] = '.';
                    }
                }
            }
            if (rnd.next(0, 1)) {
                g[N / 2][M / 2] = '.';
            }
            break;
        }
        case 6: {
            // Two separated rectangular components
            N = 5; M = 7;
            g.assign(N, string(M, '#'));
            for (int i = 0; i <= 1; ++i)
                for (int j = 0; j <= 2; ++j)
                    g[i][j] = '.';
            for (int i = 3; i <= 4; ++i)
                for (int j = 4; j <= 6; ++j)
                    g[i][j] = '.';
            break;
        }
        case 7: {
            // Snake-like simple path inside a grid
            N = rnd.next(3, 7);
            M = rnd.next(3, 7);
            g.assign(N, string(M, '#'));
            int sr = rnd.next(0, N - 1);
            int sc = rnd.next(0, M - 1);
            g[sr][sc] = '.';
            int r = sr, c = sc;
            int total = N * M;
            int lo = max(1, total / 3);
            int hi = max(lo, (total * 2) / 3);
            int pathLen = rnd.next(lo, hi);
            for (int step = 1; step < pathLen; ++step) {
                vector<pair<int,int>> neigh;
                const int dr[4] = {1, -1, 0, 0};
                const int dc[4] = {0, 0, 1, -1};
                for (int k = 0; k < 4; ++k) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if (nr >= 0 && nr < N && nc >= 0 && nc < M && g[nr][nc] == '#')
                        neigh.push_back(make_pair(nr, nc));
                }
                if (neigh.empty())
                    break;
                auto nxt = rnd.any(neigh);
                r = nxt.first;
                c = nxt.second;
                g[r][c] = '.';
            }
            break;
        }
        case 8: {
            // Medium random grid with scattered obstacles
            N = rnd.next(5, 9);
            M = rnd.next(5, 9);
            g.assign(N, string(M, '.'));
            int total = N * M;
            int bLo = total / 5;
            int bHi = total / 2;
            int blocks = rnd.next(bLo, bHi);
            vector<pair<int,int>> cells;
            cells.reserve(total);
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                    cells.push_back(make_pair(i, j));
            shuffle(cells.begin(), cells.end());
            for (int k = 0; k < blocks; ++k) {
                int i = cells[k].first;
                int j = cells[k].second;
                g[i][j] = '#';
            }
            break;
        }
    }

    // Random flips to diversify shapes
    if (rnd.next(0, 1)) {
        // horizontal flip
        for (int i = 0; i < N; ++i)
            reverse(g[i].begin(), g[i].end());
    }
    if (rnd.next(0, 1)) {
        // vertical flip
        reverse(g.begin(), g.end());
    }
    // Random transpose (if non-square, this changes N and M)
    if (rnd.next(0, 2) == 0) {
        vector<string> h(M, string(N, '#'));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                h[j][i] = g[i][j];
        g.swap(h);
        swap(N, M);
    }

    println(N, M);
    for (int i = 0; i < N; ++i)
        println(g[i]);

    return 0;
}

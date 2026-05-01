#include "testlib.h"
#include <vector>
#include <cassert>
using namespace std;

bool pathRightDown(const vector<vector<int>>& a) {
    int M = (int)a.size();
    int N = (int)a[0].size();
    if (a[0][0] == 0 || a[M - 1][N - 1] == 0) return false;
    vector<vector<char>> dp(M, vector<char>(N, 0));
    dp[0][0] = 1;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!dp[i][j] || a[i][j] == 0) continue;
            if (i + 1 < M && a[i + 1][j] == 1) dp[i + 1][j] = 1;
            if (j + 1 < N && a[i][j + 1] == 1) dp[i][j + 1] = 1;
        }
    }
    return dp[M - 1][N - 1];
}

vector<vector<int>> buildPathGrid(int N, int M, bool addRandomAround, vector<vector<char>>* onPathOut = nullptr) {
    vector<vector<int>> g(M, vector<int>(N, 0));
    vector<vector<char>> onPath(M, vector<char>(N, 0));

    int r = 0, c = 0;
    g[0][0] = 1;
    onPath[0][0] = 1;
    while (r != M - 1 || c != N - 1) {
        bool canDown = (r + 1 < M);
        bool canRight = (c + 1 < N);
        if (!canDown) {
            ++c;
        } else if (!canRight) {
            ++r;
        } else {
            if (rnd.next(0, 1) == 0) ++c;
            else ++r;
        }
        g[r][c] = 1;
        onPath[r][c] = 1;
    }

    if (addRandomAround) {
        int densType = rnd.next(0, 2);
        int p;
        if (densType == 0) p = 30;
        else if (densType == 1) p = 60;
        else p = 80;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (!onPath[i][j]) {
                    g[i][j] = (rnd.next(0, 99) < p) ? 1 : 0;
                }
            }
        }
    }

    if (onPathOut) {
        *onPathOut = onPath;
    }
    return g;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 6);
    int N = 0, M = 0; // N: width (columns), M: height (rows)
    vector<vector<int>> g;

    switch (scenario) {
        case 0: {
            // 1x1 trivial Yes
            N = 1; M = 1;
            g.assign(1, vector<int>(1, 1));
            break;
        }
        case 1: {
            // Single row, guaranteed path (all 1s)
            M = 1;
            N = rnd.next(2, 15);
            g.assign(M, vector<int>(N, 1));
            break;
        }
        case 2: {
            // Single column, guaranteed path (all 1s)
            N = 1;
            M = rnd.next(2, 15);
            g.assign(M, vector<int>(N, 1));
            break;
        }
        case 3: {
            // Small grid, only one monotone path of 1s, others 0
            N = rnd.next(2, 6);
            M = rnd.next(2, 6);
            g = buildPathGrid(N, M, false);
            break;
        }
        case 4: {
            // Small grid with guaranteed monotone path and random surroundings
            N = rnd.next(2, 6);
            M = rnd.next(2, 6);
            g = buildPathGrid(N, M, true);
            break;
        }
        case 5: {
            // Medium grid with random path and random surroundings
            N = rnd.next(5, 15);
            M = rnd.next(5, 15);
            g = buildPathGrid(N, M, true);
            break;
        }
        case 6: {
            // Grid with a "barrier" row/column that has a single gap along the path
            N = rnd.next(4, 10);
            M = rnd.next(4, 10);
            vector<vector<char>> onPath;
            g = buildPathGrid(N, M, true, &onPath);

            bool useRow = (M >= 3 && (N < 3 || rnd.next(0, 1) == 0));
            if (useRow) {
                int r = rnd.next(1, M - 2);
                for (int j = 0; j < N; ++j) {
                    if (!onPath[r][j]) g[r][j] = 0;
                }
            } else {
                int c = rnd.next(1, N - 2);
                for (int i = 0; i < M; ++i) {
                    if (!onPath[i][c]) g[i][c] = 0;
                }
            }
            break;
        }
    }

    // Ensure endpoints are passable
    g[0][0] = 1;
    g[M - 1][N - 1] = 1;

    // Safety check: ensure a right/down-only path exists
    assert(pathRightDown(g));

    // Output: N (width), M (height), then M rows of N integers
    println(N, M);
    for (int i = 0; i < M; ++i)
        println(g[i]);

    return 0;
}

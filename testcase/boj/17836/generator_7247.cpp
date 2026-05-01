#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid size
    int N = rnd.next(3, 12);
    int M = rnd.next(3, 12);
    // Scenario: light, medium, heavy walls
    int scenario = rnd.next(0, 2);
    double density;
    if (scenario == 0) density = rnd.next(0.0, 0.2);
    else if (scenario == 1) density = rnd.next(0.3, 0.6);
    else density = rnd.next(0.6, 0.9);
    // Build grid, 0-empty,1-wall
    vector<vector<int>> a(N, vector<int>(M, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if ((i == 0 && j == 0) || (i == N-1 && j == M-1)) continue;
            if (rnd.next() < density) a[i][j] = 1;
        }
    }
    // Collect empties for Gram placement
    vector<pair<int,int>> empties;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (!(i == 0 && j == 0) && !(i == N-1 && j == M-1) && a[i][j] == 0)
                empties.emplace_back(i, j);
    // Guarantee at least one place
    if (empties.empty()) {
        int gi, gj;
        do { gi = rnd.next(0, N-1); gj = rnd.next(0, M-1); }
        while ((gi == 0 && gj == 0) || (gi == N-1 && gj == M-1));
        a[gi][gj] = 0;
        empties.emplace_back(gi, gj);
    }
    // Place Gram (2)
    auto g = rnd.any(empties);
    a[g.first][g.second] = 2;
    // Compute minimal distance without walls
    int dmin = N + M - 2;
    // Time limit scenario: tight, generous, impossible
    int tch = rnd.next(0, 2);
    int T;
    if (tch == 0) {
        int lo = max(1, dmin - 1);
        int hi = dmin + rnd.next(0, 2);
        T = rnd.next(lo, hi);
    } else if (tch == 1) {
        int lo = dmin + max(N, M);
        int hi = dmin + (N * M) / 2;
        T = rnd.next(lo, max(lo, hi));
    } else {
        int hi = max(1, dmin - 2);
        T = rnd.next(1, hi);
    }
    T = min(T, 10000);
    // Output
    println(N, M, T);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d%c", a[i][j], j + 1 == M ? '\n' : ' ');
        }
    }
    return 0;
}

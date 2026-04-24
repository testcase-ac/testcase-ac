#include "testlib.h"
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Dimensions
    int N = rnd.next(2, 10);
    int M = rnd.next(2, 10);

    // Prepare positions
    vector<pair<int,int>> border, inner, all;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            all.emplace_back(i, j);
            if (i == 0 || j == 0 || i == N-1 || j == M-1)
                border.emplace_back(i, j);
            else
                inner.emplace_back(i, j);
        }
    }

    // Helper to pick one pos with fallback
    auto pick = [&](const vector<pair<int,int>>& prefs, const vector<pair<int,int>>& avoid) {
        vector<pair<int,int>> cand;
        for (auto &p : prefs) {
            bool ok = true;
            for (auto &a : avoid) if (p == a) { ok = false; break; }
            if (ok) cand.push_back(p);
        }
        if (cand.empty()) {
            for (auto &p : all) {
                bool ok = true;
                for (auto &a : avoid) if (p == a) { ok = false; break; }
                if (ok) cand.push_back(p);
            }
        }
        return rnd.any(cand);
    };

    // Place characters
    vector<pair<int,int>> used;
    pair<int,int> Y = pick(rnd.next() < 0.5 ? border : inner, used);
    used.push_back(Y);
    pair<int,int> T = pick(rnd.next() < 0.5 ? border : inner, used);
    used.push_back(T);
    pair<int,int> V = pick(rnd.next() < 0.5 ? border : inner, used);
    used.push_back(V);

    // Island density hyperparameter
    double p;
    double r = rnd.next();
    if (r < 0.2) p = 0.0;
    else if (r < 0.4) p = 1.0;
    else p = rnd.next();

    // Build grid
    vector<string> grid(N, string(M, '.'));
    grid[Y.first][Y.second] = 'Y';
    grid[T.first][T.second] = 'T';
    grid[V.first][V.second] = 'V';
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if ((i==Y.first && j==Y.second) ||
                (i==T.first && j==T.second) ||
                (i==V.first && j==V.second))
                continue;
            if (rnd.next() < p) grid[i][j] = 'I';
        }
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(grid[i]);
    }
    return 0;
}

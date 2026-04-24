#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameter for grid size: small or medium
    int N = (rnd.next(0, 2) == 0 ? rnd.next(2, 5) : rnd.next(6, 20));
    int M = (rnd.next(0, 2) == 0 ? rnd.next(2, 5) : rnd.next(6, 20));
    int maxNM = max(N, M);
    // Hyperparameter for K: sometimes small, sometimes large
    int K;
    if (rnd.next(0, 1) == 0) {
        int hi = min(maxNM, 5);
        K = rnd.next(1, hi);
    } else {
        int lo = min(maxNM, 6);
        K = rnd.next(lo, maxNM);
    }
    // Build grid
    vector<string> g(N, string(M, '.'));
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        // Random walls
        double d = rnd.next(0.0, 0.7);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (rnd.next() < d) g[i][j] = '#';
            }
        }
    } else if (mode == 1) {
        // Vertical stripe walls
        int w = rnd.next(1, max(1, M / 4));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (((j / w) % 2) == 0) g[i][j] = '#';
                else if (rnd.next() < 0.1) g[i][j] = '#';
            }
        }
    } else {
        // Horizontal stripe walls
        int w = rnd.next(1, max(1, N / 4));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (((i / w) % 2) == 0) g[i][j] = '#';
                else if (rnd.next() < 0.1) g[i][j] = '#';
            }
        }
    }
    // Collect empty cells
    vector<pair<int,int>> emp;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (g[i][j] == '.') emp.emplace_back(i, j);
        }
    }
    // Ensure at least two empty cells
    if ((int)emp.size() < 2) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                g[i][j] = '.';
        emp.clear();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                emp.emplace_back(i, j);
    }
    // Pick distinct start and end
    auto st = rnd.any(emp);
    auto ed = rnd.any(emp);
    while (ed == st) ed = rnd.any(emp);
    // Output
    println(N, M, K);
    for (int i = 0; i < N; i++) {
        println(g[i]);
    }
    // Convert to 1-based
    println(st.first+1, st.second+1, ed.first+1, ed.second+1);
    return 0;
}

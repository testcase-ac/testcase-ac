#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size
    int N = rnd.next(2, 10);

    // Adjacency matrix to avoid duplicates
    vector<vector<bool>> has(N+1, vector<bool>(N+1, false));
    vector<vector<int>> adj(N+1);

    // Hyperparameter: choose graph shape
    int graphType = rnd.next(0, 2);
    if (graphType == 0) {
        // Erdos-Renyi with random density
        int p10 = rnd.next(1, 9);
        double p = p10 / 10.0;
        for (int i = 1; i <= N; i++) {
            for (int j = i+1; j <= N; j++) {
                if (rnd.next() < p) {
                    has[i][j] = has[j][i] = true;
                }
            }
        }
    } else if (graphType == 1) {
        // Chain graph
        for (int i = 1; i < N; i++) {
            has[i][i+1] = has[i+1][i] = true;
        }
        // plus some random extras
        int extra = rnd.next(0, N);
        for (int it = 0; it < extra; it++) {
            int u = rnd.next(1, N), v = rnd.next(1, N);
            if (u != v) has[u][v] = has[v][u] = true;
        }
    } else {
        // Star graph
        int center = rnd.next(1, N);
        for (int i = 1; i <= N; i++) {
            if (i != center) has[center][i] = has[i][center] = true;
        }
        // plus some random extras
        int extra = rnd.next(0, N/2);
        for (int it = 0; it < extra; it++) {
            int u = rnd.next(1, N), v = rnd.next(1, N);
            if (u != v) has[u][v] = has[v][u] = true;
        }
    }

    // Build adjacency lists
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (has[i][j]) adj[i].push_back(j);
        }
    }

    // Hyperparameter: choose initial rumor spreaders
    int M = rnd.next(1, N);
    vector<int> seeds;
    int seedType = rnd.next(0, 1);
    if (seedType == 0) {
        // purely random distinct
        seeds.resize(N);
        for (int i = 0; i < N; i++) seeds[i] = i+1;
        shuffle(seeds.begin(), seeds.end());
        seeds.resize(M);
    } else {
        // cluster around one node
        int c = rnd.next(1, N);
        vector<int> pool = adj[c];
        shuffle(pool.begin(), pool.end());
        for (int x : pool) {
            if ((int)seeds.size() < M) seeds.push_back(x);
        }
        // fill remaining randomly
        vector<int> all(N);
        for (int i = 0; i < N; i++) all[i] = i+1;
        shuffle(all.begin(), all.end());
        for (int x : all) {
            if ((int)seeds.size() >= M) break;
            if (x == c) continue;
            bool ok = true;
            for (int y : seeds) if (y == x) { ok = false; break; }
            if (ok) seeds.push_back(x);
        }
        // if still short, add the center
        if ((int)seeds.size() < M) seeds.push_back(c);
        // trim
        shuffle(seeds.begin(), seeds.end());
        seeds.resize(M);
    }

    // Output
    println(N);
    for (int i = 1; i <= N; i++) {
        vector<int> line = adj[i];
        shuffle(line.begin(), line.end());
        line.push_back(0);
        println(line);
    }
    println(M);
    println(seeds);

    return 0;
}

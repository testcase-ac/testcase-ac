#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        // Small number of nodes
        int N = rnd.next(1, 10);

        // Track used edges
        vector<vector<bool>> used(N, vector<bool>(N, false));
        vector<pair<int,int>> edges;

        // Diversify graph shapes
        int type = rnd.next(0, 4);
        if (type == 0) {
            // Random sparse graph
            double p = rnd.next() * 0.4 + 0.1;  // [0.1,0.5)
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (!used[i][j] && rnd.next() < p) {
                        used[i][j] = true;
                        edges.emplace_back(i, j);
                    }
                }
            }
        }
        else if (type == 1) {
            // Random dense graph
            double p = rnd.next() * 0.4 + 0.5;  // [0.5,0.9)
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (!used[i][j] && rnd.next() < p) {
                        used[i][j] = true;
                        edges.emplace_back(i, j);
                    }
                }
            }
        }
        else if (type == 2) {
            // Simple directed cycle plus extras
            if (N >= 1) {
                for (int i = 0; i < N; ++i) {
                    int j = (i + 1) % N;
                    if (!used[i][j]) {
                        used[i][j] = true;
                        edges.emplace_back(i, j);
                    }
                }
                int extra = rnd.next(0, N);
                for (int k = 0; k < extra; ++k) {
                    int a = rnd.next(0, N - 1);
                    int b = rnd.next(0, N - 1);
                    if (!used[a][b]) {
                        used[a][b] = true;
                        edges.emplace_back(a, b);
                    }
                }
            }
        }
        else if (type == 3) {
            // Tree-like DAG plus extras
            for (int i = 1; i < N; ++i) {
                int j = rnd.next(0, i - 1);
                if (!used[j][i]) {
                    used[j][i] = true;
                    edges.emplace_back(j, i);
                }
            }
            int extra = rnd.next(0, N);
            for (int k = 0; k < extra; ++k) {
                int a = rnd.next(0, N - 1);
                int b = rnd.next(0, N - 1);
                if (!used[a][b]) {
                    used[a][b] = true;
                    edges.emplace_back(a, b);
                }
            }
        }
        else {
            // Two disconnected components
            if (N >= 2) {
                vector<int> nodes(N);
                for (int i = 0; i < N; ++i) nodes[i] = i;
                shuffle(nodes.begin(), nodes.end());
                int split = rnd.next(1, N - 1);
                vector<int> g1(nodes.begin(), nodes.begin() + split);
                vector<int> g2(nodes.begin() + split, nodes.end());
                double p1 = rnd.next() * 0.5 + 0.2;  // [0.2,0.7)
                double p2 = rnd.next() * 0.5 + 0.2;
                for (int i : g1) for (int j : g1) {
                    if (!used[i][j] && rnd.next() < p1) {
                        used[i][j] = true;
                        edges.emplace_back(i, j);
                    }
                }
                for (int i : g2) for (int j : g2) {
                    if (!used[i][j] && rnd.next() < p2) {
                        used[i][j] = true;
                        edges.emplace_back(i, j);
                    }
                }
            }
        }

        // Ensure at least 1 edge
        if (edges.empty()) {
            int a = rnd.next(0, N - 1);
            int b = rnd.next(0, N - 1);
            edges.emplace_back(a, b);
        }

        // Shuffle and cap size for hand-checkability
        shuffle(edges.begin(), edges.end());
        int cap = min((int)edges.size(), 20);
        int M = rnd.next(1, cap);
        edges.resize(M);

        // Output this test case
        println(N, M);
        for (auto &e : edges) {
            println(e.first, e.second);
        }

        // Blank line between test cases
        if (tc + 1 < T) println("");
    }

    return 0;
}

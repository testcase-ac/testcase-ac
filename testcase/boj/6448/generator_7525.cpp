#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 4);
    for (int tc = 0; tc < T; tc++) {
        int N = rnd.next(1, 15);
        println(N);
        vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
        vector<vector<pair<int,int>>> adj(N+1);
        if (N == 1) {
            // no contacts
            println(0);
            continue;
        }
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            // strongly connected cycle + extra
            vector<int> perm(N);
            for (int i = 0; i < N; i++) perm[i] = i+1;
            shuffle(perm.begin(), perm.end());
            // cycle
            for (int i = 0; i < N; i++) {
                int u = perm[i];
                int v = perm[(i+1)%N];
                int w = rnd.next(1, 10);
                used[u][v] = true;
                adj[u].emplace_back(v, w);
            }
            // extra edges
            double p = rnd.next(1, 10) / 10.0;
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    if (i == j || used[i][j]) continue;
                    if (rnd.next() < p) {
                        int w = rnd.next(1, 10);
                        used[i][j] = true;
                        adj[i].emplace_back(j, w);
                    }
                }
            }
        } else if (mode == 1) {
            // mid density
            double p = rnd.next(4, 8) / 10.0;
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    if (i == j) continue;
                    if (rnd.next() < p) {
                        int w = rnd.next(1, 10);
                        if (!used[i][j]) {
                            used[i][j] = true;
                            adj[i].emplace_back(j, w);
                        }
                    }
                }
            }
        } else {
            // sparse
            double p = rnd.next(1, 3) / 10.0;
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    if (i == j) continue;
                    if (rnd.next() < p) {
                        int w = rnd.next(1, 10);
                        if (!used[i][j]) {
                            used[i][j] = true;
                            adj[i].emplace_back(j, w);
                        }
                    }
                }
            }
        }
        // output contacts
        for (int i = 1; i <= N; i++) {
            int d = adj[i].size();
            printf("%d", d);
            for (auto &pr : adj[i]) {
                printf(" %d %d", pr.first, pr.second);
            }
            printf("\n");
        }
    }
    println(0);
    return 0;
}

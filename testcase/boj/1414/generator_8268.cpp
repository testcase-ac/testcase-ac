#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of computers
    int N = rnd.next(1, 15);
    // Probability to force connectivity
    bool forceConn = rnd.next(0, 1);
    // Edge density for random non-tree edges
    double density = rnd.next(0.0, 1.0);

    vector<string> mat(N, string(N, '0'));
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 0);
    // If forcing connectivity, build a random spanning tree
    if (forceConn && N > 1) {
        shuffle(perm.begin(), perm.end());
        for (int i = 1; i < N; i++) {
            int u = perm[i-1], v = perm[i];
            bool dir = rnd.next(0, 1);
            int len = rnd.next(1, 52);
            char c = (len <= 26 ? char('a' + len - 1) : char('A' + (len - 27)));
            if (dir) mat[u][v] = c;
            else     mat[v][u] = c;
        }
    }
    // Fill self-loops and other entries
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                // Self-loop, can always be donated
                if (rnd.next(0, 1)) {
                    int len = rnd.next(1, 52);
                    mat[i][j] = (len <= 26 ? char('a' + len - 1) : char('A' + (len - 27)));
                } else {
                    mat[i][j] = '0';
                }
            } else {
                // If part of the spanning tree, it's already set
                if (mat[i][j] != '0') continue;
                // Randomly add a cable with given density
                if (rnd.next() < density) {
                    int len = rnd.next(1, 52);
                    mat[i][j] = (len <= 26 ? char('a' + len - 1) : char('A' + (len - 27)));
                } else {
                    mat[i][j] = '0';
                }
            }
        }
    }
    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(mat[i]);
    }
    return 0;
}

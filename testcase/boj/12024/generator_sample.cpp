#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

static void addEdge(vector<vector<int>>& a, int u, int v) {
    if (u == v) {
        return;
    }
    a[u][v] = 1;
    a[v][u] = 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 14);
    if (mode == 2 || mode == 3) {
        n = rnd.next(4, 14);
    }

    vector<vector<int>> a(n, vector<int>(n, 0));

    if (mode == 0) {
        double p = rnd.next(0.0, 0.35);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < p) {
                    addEdge(a, i, j);
                }
            }
        }
    } else if (mode == 1) {
        double p = rnd.next(0.55, 1.0);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < p) {
                    addEdge(a, i, j);
                }
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            addEdge(a, i, (i + 1) % n);
        }
        int extra = rnd.next(0, n);
        for (int t = 0; t < extra; ++t) {
            addEdge(a, rnd.next(0, n - 1), rnd.next(0, n - 1));
        }
    } else if (mode == 3) {
        int left = rnd.next(1, n - 1);
        for (int i = 0; i < left; ++i) {
            for (int j = left; j < n; ++j) {
                if (rnd.next() < 0.75) {
                    addEdge(a, i, j);
                }
            }
        }
    } else if (mode == 4) {
        int clique = rnd.next(1, n);
        for (int i = 0; i < clique; ++i) {
            for (int j = i + 1; j < clique; ++j) {
                addEdge(a, i, j);
            }
        }
        int extra = rnd.next(0, n);
        for (int t = 0; t < extra; ++t) {
            addEdge(a, rnd.next(0, n - 1), rnd.next(0, n - 1));
        }
    } else {
        int center = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            if (i != center && rnd.next(0, 1)) {
                addEdge(a, center, i);
            }
        }
        int extra = rnd.next(0, n);
        for (int t = 0; t < extra; ++t) {
            addEdge(a, rnd.next(0, n - 1), rnd.next(0, n - 1));
        }
    }

    vector<int> perm(n);
    for (int i = 0; i < n; ++i) {
        perm[i] = i;
    }
    shuffle(perm.begin(), perm.end());

    println(n);
    for (int i = 0; i < n; ++i) {
        vector<int> row;
        for (int j = 0; j < n; ++j) {
            row.push_back(a[perm[i]][perm[j]]);
        }
        println(row);
    }

    return 0;
}

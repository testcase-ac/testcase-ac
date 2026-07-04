#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int INF = 9999;

void printMatrix(const vector<vector<int>>& g) {
    int n = (int)g.size();
    println(n);
    for (int i = 0; i < n; ++i) {
        println(g[i]);
    }
}

vector<vector<int>> emptyMatrix(int n) {
    vector<vector<int>> g(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        g[i][i] = 0;
    }
    return g;
}

void relaxThroughPrefix(vector<vector<int>>& g, int lastMiddle) {
    int n = (int)g.size();
    for (int w = 0; w < lastMiddle; ++w) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                g[u][v] = min(g[u][v], g[u][w] + g[w][v]);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 4) {
        n = rnd.next(12, 30);
    } else {
        n = rnd.next(1, 10);
    }

    vector<vector<int>> g = emptyMatrix(n);

    if (mode == 0) {
        double edgeProb = rnd.next(0.0, 0.25);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < edgeProb) {
                    g[i][j] = g[j][i] = 1;
                }
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i + 1 < n; ++i) {
            g[i][i + 1] = g[i + 1][i] = 1;
        }
        int extraEdges = rnd.next(0, max(0, n - 2));
        for (int it = 0; it < extraEdges; ++it) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 1);
            if (a != b) {
                g[a][b] = g[b][a] = 1;
            }
        }
        relaxThroughPrefix(g, rnd.next(0, n));
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && rnd.next() < 0.35) {
                    g[i][j] = rnd.any(vector<int>{1, 2, 3, INF});
                }
            }
        }
    } else if (mode == 3) {
        int split = rnd.next(1, n);
        for (int i = 0; i < split; ++i) {
            for (int j = 0; j < split; ++j) {
                if (i != j) {
                    g[i][j] = min(INF, abs(i - j) + rnd.next(0, 2));
                }
            }
        }
        for (int i = split; i < n; ++i) {
            for (int j = split; j < n; ++j) {
                if (i != j && rnd.next() < 0.70) {
                    g[i][j] = rnd.next(1, 8);
                }
            }
        }
    } else {
        double edgeProb = rnd.next(0.15, 0.65);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < edgeProb) {
                    g[i][j] = g[j][i] = 1;
                }
            }
        }
        relaxThroughPrefix(g, max(0, n - 1));
    }

    for (int i = 0; i < n; ++i) {
        g[i][i] = 0;
    }

    printMatrix(g);
    return 0;
}

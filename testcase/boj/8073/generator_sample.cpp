#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1000000000;

void floyd(vector<vector<int>>& d) {
    int n = d.size();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

vector<vector<int>> lineMetric(int n) {
    vector<int> x(n);
    for (int i = 1; i < n; ++i) {
        x[i] = x[i - 1] + rnd.next(0, 8);
    }

    vector<vector<int>> d(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            d[i][j] = abs(x[i] - x[j]);
        }
    }
    return d;
}

vector<vector<int>> starMetric(int n) {
    vector<int> radius(n);
    int zeroLeaves = rnd.next(0, min(2, n - 1));
    for (int i = 1; i < n; ++i) {
        radius[i] = (i <= zeroLeaves ? 0 : rnd.next(1, 20));
    }
    shuffle(radius.begin() + 1, radius.end());

    vector<vector<int>> d(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            d[i][j] = d[j][i] = radius[i] + radius[j];
        }
    }
    return d;
}

vector<vector<int>> treeMetric(int n) {
    vector<vector<int>> d(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        d[i][i] = 0;
    }

    for (int v = 1; v < n; ++v) {
        int p = rnd.next(0, v - 1);
        int w = rnd.next(1, 12);
        d[v][p] = d[p][v] = w;
    }

    floyd(d);
    return d;
}

vector<vector<int>> graphMetric(int n) {
    vector<vector<int>> d(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        d[i][i] = 0;
    }

    for (int i = 1; i < n; ++i) {
        int p = rnd.next(0, i - 1);
        int w = rnd.next(1, 25);
        d[i][p] = d[p][i] = min(d[i][p], w);
    }

    int extra = rnd.next(0, n * (n - 1) / 3);
    for (int e = 0; e < extra; ++e) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 1);
        if (a == b) {
            --e;
            continue;
        }
        int w = rnd.next(1, 35);
        d[a][b] = d[b][a] = min(d[a][b], w);
    }

    floyd(d);
    return d;
}

void printMatrix(const vector<vector<int>>& d) {
    println(static_cast<int>(d.size()));
    for (const vector<int>& row : d) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 12);

    vector<vector<int>> d;
    if (n == 1) {
        d = vector<vector<int>>(1, vector<int>(1, 0));
    } else if (mode == 0) {
        d = lineMetric(n);
    } else if (mode == 1) {
        d = starMetric(n);
    } else if (mode == 2) {
        d = treeMetric(n);
    } else {
        d = graphMetric(n);
    }

    printMatrix(d);
    return 0;
}

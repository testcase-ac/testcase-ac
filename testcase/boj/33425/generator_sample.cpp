#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAX_W = 1000000;

void setEdge(vector<vector<int>>& a, int u, int v, int w) {
    a[u][v] = w;
    a[v][u] = w;
}

void printMatrix(const vector<vector<int>>& a) {
    cout << a.size() << '\n';
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = 0; j < (int)a.size(); ++j) {
            if (j) cout << ' ';
            cout << a[i][j];
        }
        cout << '\n';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 1;
    if (mode != 0) {
        n = rnd.next(2, 10);
    }

    vector<vector<int>> a(n, vector<int>(n, 0));

    if (mode == 0) {
        printMatrix(a);
        return 0;
    }

    if (mode == 1) {
        int maxWeight = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                setEdge(a, i, j, rnd.next(1, maxWeight));
            }
        }
    } else if (mode == 2) {
        vector<int> pos(n, 0);
        for (int i = 1; i < n; ++i) {
            pos[i] = pos[i - 1] + rnd.next(1, 12);
        }
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int dist = pos[i] > pos[j] ? pos[i] - pos[j] : pos[j] - pos[i];
                setEdge(a, i, j, dist);
            }
        }
    } else if (mode == 3) {
        int center = rnd.next(n);
        vector<int> spoke(n, 0);
        for (int i = 0; i < n; ++i) {
            if (i != center) {
                spoke[i] = rnd.next(1, 25);
                setEdge(a, center, i, spoke[i]);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (i == center || j == center) continue;
                int slack = rnd.next(0, 5);
                setEdge(a, i, j, min(MAX_W, spoke[i] + spoke[j] + slack));
            }
        }
    } else if (mode == 4) {
        vector<int> group(n, 0);
        int groups = rnd.next(2, min(4, n));
        for (int i = 0; i < n; ++i) {
            group[i] = rnd.next(groups);
        }
        for (int i = 0; i < groups; ++i) {
            group[i] = i;
        }
        shuffle(group.begin(), group.end());
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int base = (group[i] == group[j] ? rnd.next(1, 9) : rnd.next(20, 80));
                if (rnd.next(4) == 0) {
                    base += rnd.next(100, 300);
                }
                setEdge(a, i, j, base);
            }
        }
    } else {
        n = rnd.next(2, 8);
        a.assign(n, vector<int>(n, 0));
        int special = rnd.next(3);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int w;
                if (special == 0) {
                    w = MAX_W - rnd.next(0, 20);
                } else if (special == 1) {
                    w = (i + j) % 2 == 0 ? 1 : rnd.next(2, 6);
                } else {
                    w = rnd.next(1, 1000);
                    if (rnd.next(5) == 0) w = MAX_W;
                }
                setEdge(a, i, j, w);
            }
        }
    }

    printMatrix(a);
    return 0;
}

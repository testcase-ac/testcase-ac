#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 25);
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(26, 120);
    }

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i + 1;
    }
    shuffle(order.begin(), order.end());

    vector<int> par(n + 1);
    for (int i = 1; i <= n; ++i) {
        par[i] = i;
    }

    if (mode == 0) {
        // All singleton sets.
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) {
            par[order[i]] = order[i - 1];
        }
    } else if (mode == 2) {
        int root = order[0];
        for (int i = 1; i < n; ++i) {
            par[order[i]] = root;
        }
    } else if (mode == 3) {
        int roots = rnd.next(1, n);
        for (int i = roots; i < n; ++i) {
            par[order[i]] = order[rnd.next(0, i - 1)];
        }
    } else if (mode == 4) {
        for (int i = 1; i < n; ++i) {
            par[order[i]] = order[(i - 1) / 2];
        }
    } else {
        int roots = rnd.next(1, n);
        for (int i = roots; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                par[order[i]] = order[rnd.next(0, roots - 1)];
            } else {
                par[order[i]] = order[rnd.next(0, i - 1)];
            }
        }
    }

    int nonRoots = 0;
    for (int i = 1; i <= n; ++i) {
        nonRoots += (par[i] != i);
    }

    int m = rnd.next(1, min(20, max(1, n)));
    int padding = rnd.next(0, 12);
    if (rnd.next(0, 4) == 0) {
        padding = 0;
    }
    int q = nonRoots + m + padding;

    vector<int> returned(m);
    for (int i = 0; i < m; ++i) {
        if (rnd.next(0, 3) == 0) {
            returned[i] = order[rnd.next(0, n - 1)];
        } else {
            returned[i] = rnd.next(1, n);
        }
    }

    println(n, q);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << par[i];
    }
    cout << '\n';
    println(m);
    for (int v : returned) {
        println(v);
    }

    return 0;
}

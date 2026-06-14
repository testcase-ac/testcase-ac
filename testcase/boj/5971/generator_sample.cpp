#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, 40);
    int m = rnd.next(1, 50);

    vector<int> parent(n + 1, 1);
    vector<vector<int>> children(n + 1);
    children[1].clear();

    for (int i = 2; i <= n; ++i) {
        if (mode == 0) {
            parent[i] = i - 1;
        } else if (mode == 1) {
            parent[i] = 1;
        } else if (mode == 2) {
            parent[i] = max(1, i / 2);
        } else if (mode == 3) {
            parent[i] = rnd.next(1, i - 1);
        } else {
            int chainLen = max(1, n / 3);
            if (i <= chainLen + 1) {
                parent[i] = i - 1;
            } else {
                parent[i] = rnd.next(1, chainLen + 1);
            }
        }
    }

    vector<int> depth(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        children[parent[i]].push_back(i);
        depth[i] = depth[parent[i]] + 1;
    }

    auto ancestor = [&](int v) {
        int steps = rnd.next(0, depth[v]);
        while (steps-- > 0) {
            v = parent[v];
        }
        return v;
    };

    println(n, m);
    for (int i = 2; i <= n; ++i) {
        println(parent[i]);
    }

    for (int q = 0; q < m; ++q) {
        int type = rnd.next(6);
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);

        if (type == 0) {
            b = a;
        } else if (type == 1) {
            a = 1;
        } else if (type == 2) {
            b = ancestor(a);
        } else if (type == 3) {
            int base = rnd.next(1, n);
            a = ancestor(base);
            b = base;
        } else if (type == 4) {
            vector<int> branching;
            for (int i = 1; i <= n; ++i) {
                if (children[i].size() >= 2) {
                    branching.push_back(i);
                }
            }
            if (!branching.empty()) {
                int p = rnd.any(branching);
                vector<int> kids = children[p];
                shuffle(kids.begin(), kids.end());
                a = kids[0];
                b = kids[1];
            }
        }

        if (rnd.next(2) == 0) {
            swap(a, b);
        }
        println(a, b);
    }

    return 0;
}

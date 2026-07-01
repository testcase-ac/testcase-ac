#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 14);
    int q = rnd.next(1, 24);

    vector<int> parent(n + 1, 1);
    vector<vector<int>> children(n + 1);

    for (int i = 2; i <= n; ++i) {
        if (mode == 0) {
            parent[i] = i - 1;
        } else if (mode == 1) {
            parent[i] = 1;
        } else if (mode == 2) {
            parent[i] = max(1, i / 2);
        } else {
            parent[i] = rnd.next(1, i - 1);
        }
        children[parent[i]].push_back(i);
    }

    if (mode == 4 || mode == 5) {
        vector<int> oldToNew(n + 1);
        vector<int> labels;
        for (int i = 2; i <= n; ++i) {
            labels.push_back(i);
        }
        shuffle(labels.begin(), labels.end());
        oldToNew[1] = 1;
        for (int i = 2; i <= n; ++i) {
            oldToNew[i] = labels[i - 2];
        }

        vector<int> relabeledParent(n + 1, 1);
        for (int oldNode = 2; oldNode <= n; ++oldNode) {
            relabeledParent[oldToNew[oldNode]] = oldToNew[parent[oldNode]];
        }
        parent = relabeledParent;
    }

    vector<int> depth(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        int v = i;
        vector<int> path;
        while (v != 1 && depth[v] == 0) {
            path.push_back(v);
            v = parent[v];
        }
        int d = depth[v];
        reverse(path.begin(), path.end());
        for (int u : path) {
            depth[u] = ++d;
        }
    }

    vector<int> leaves;
    vector<int> childCount(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        ++childCount[parent[i]];
    }
    for (int i = 1; i <= n; ++i) {
        if (childCount[i] == 0) {
            leaves.push_back(i);
        }
    }

    println(n, q);
    for (int i = 2; i <= n; ++i) {
        println(parent[i]);
    }

    for (int i = 0; i < q; ++i) {
        int opChoice = rnd.next(0, 99);
        int v;
        if (i == 0 || opChoice < 45) {
            if (!leaves.empty() && rnd.next(0, 99) < 65) {
                v = rnd.any(leaves);
            } else {
                v = rnd.next(1, n);
            }
            printf("Q %d\n", v);
        } else {
            int pick = rnd.next(0, 99);
            if (pick < 20) {
                v = 1;
            } else if (pick < 55 && !leaves.empty()) {
                v = rnd.any(leaves);
            } else {
                v = rnd.next(1, n);
            }
            printf("M %d\n", v);
        }
    }

    return 0;
}

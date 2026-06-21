#include "testlib.h"

#include <functional>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(n, 2000, "M");
    inf.readEoln();

    vector<int> a(n + 1), leftChild(n + 1), rightChild(n + 1);
    vector<int> parent(n + 1, 0);
    bool hasErased = false;

    for (int i = 1; i <= n; ++i) {
        a[i] = inf.readInt(-1, m, "a_i");
        ensuref(a[i] == -1 || a[i] >= 1, "a_%d must be -1 or in [1, M]", i);
        if (a[i] == -1) {
            hasErased = true;
        }
        inf.readSpace();

        leftChild[i] = inf.readInt(-1, n, "left_i");
        ensuref(leftChild[i] != 0, "left child of node %d must be -1 or in [1, N]", i);
        inf.readSpace();

        rightChild[i] = inf.readInt(-1, n, "right_i");
        ensuref(rightChild[i] != 0, "right child of node %d must be -1 or in [1, N]", i);
        ensuref(leftChild[i] == -1 || rightChild[i] == -1 || leftChild[i] != rightChild[i],
                "node %d has the same left and right child %d", i, leftChild[i]);
        inf.readEoln();

        if (leftChild[i] != -1) {
            ensuref(parent[leftChild[i]] == 0, "node %d has multiple parents", leftChild[i]);
            parent[leftChild[i]] = i;
        }
        if (rightChild[i] != -1) {
            ensuref(parent[rightChild[i]] == 0, "node %d has multiple parents", rightChild[i]);
            parent[rightChild[i]] = i;
        }
    }

    ensuref(hasErased, "at least one node value must be erased");
    ensuref(parent[1] == 0, "root node 1 must not have a parent");

    vector<int> seen(n + 1, 0), order;
    function<void(int)> dfs = [&](int v) {
        ensuref(!seen[v], "cycle or duplicate reachability at node %d", v);
        seen[v] = 1;
        if (leftChild[v] != -1) {
            dfs(leftChild[v]);
        }
        order.push_back(a[v]);
        if (rightChild[v] != -1) {
            dfs(rightChild[v]);
        }
    };
    dfs(1);

    ensuref((int)order.size() == n, "tree rooted at 1 reaches %d nodes, expected %d",
            (int)order.size(), n);
    for (int i = 1; i <= n; ++i) {
        ensuref(seen[i], "node %d is not reachable from root 1", i);
    }

    int low = 1;
    int erasedStreak = 0;
    for (int x : order) {
        if (x == -1) {
            ++erasedStreak;
            continue;
        }

        ensuref(x >= low, "known values in inorder traversal are not strictly increasing");
        ensuref(x - low >= erasedStreak,
                "no positive completion before known value %d with %d erased nodes",
                x, erasedStreak);
        low = x + 1;
        erasedStreak = 0;
    }
    ensuref(m + 1 - low >= erasedStreak,
            "no positive completion after the last known value with %d erased nodes",
            erasedStreak);

    inf.readEof();
}

#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = (mode == 0 ? 1 : rnd.next(2, 12));
    int q = rnd.next(1, 18);

    vector<int> parent(n + 1, 0);
    if (n >= 2) {
        if (mode == 1) {
            for (int v = 2; v <= n; ++v) parent[v] = v - 1;
        } else if (mode == 2) {
            for (int v = 2; v <= n; ++v) parent[v] = 1;
        } else if (mode == 3) {
            for (int v = 2; v <= n; ++v) parent[v] = v / 2;
        } else {
            for (int v = 2; v <= n; ++v) parent[v] = rnd.next(1, v - 1);
        }
    }

    vector<vector<int>> children(n + 1);
    for (int v = 2; v <= n; ++v) children[parent[v]].push_back(v);

    vector<int> preorder;
    vector<int> stack = {1};
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        preorder.push_back(v);
        shuffle(children[v].begin(), children[v].end());
        for (int to : children[v]) stack.push_back(to);
    }

    vector<int> deletionOrder;
    for (int v = 2; v <= n; ++v) deletionOrder.push_back(v);
    if (mode == 1) {
        reverse(deletionOrder.begin(), deletionOrder.end());
    } else if (mode == 2) {
        shuffle(deletionOrder.begin(), deletionOrder.end());
    } else if (mode == 3) {
        sort(deletionOrder.begin(), deletionOrder.end(), [&](int lhs, int rhs) {
            return parent[lhs] == parent[rhs] ? lhs < rhs : parent[lhs] < parent[rhs];
        });
    } else {
        vector<int> byDfs;
        for (int v : preorder) {
            if (v != 1) byDfs.push_back(v);
        }
        deletionOrder = byDfs;
    }

    vector<vector<int>> operations;
    for (int v : deletionOrder) operations.push_back({0, v});

    for (int i = 0; i < q; ++i) {
        int c;
        int d;
        if (n == 1) {
            c = d = 1;
        } else if (i % 5 == 0) {
            c = rnd.next(1, n);
            d = c;
        } else if (i % 5 == 1) {
            int child = rnd.next(2, n);
            c = parent[child];
            d = child;
        } else if (i % 5 == 2 && preorder.size() >= 2) {
            c = preorder.front();
            d = preorder.back();
        } else {
            c = rnd.next(1, n);
            d = rnd.next(1, n);
        }
        operations.push_back({1, c, d});
    }
    shuffle(operations.begin(), operations.end());

    println(n, q);
    for (int v = 2; v <= n; ++v) println(parent[v]);
    for (const vector<int>& op : operations) {
        if (op[0] == 0) {
            println(op[0], op[1]);
        } else {
            println(op[0], op[1], op[2]);
        }
    }

    return 0;
}

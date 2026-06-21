#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long K_MAX = 1000000000000000000LL;
    const long long VISIT_CAP = K_MAX;

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long k = inf.readLong(1LL, K_MAX, "K");
    inf.readEoln();

    vector<int> left(n + 1), right(n + 1), parent(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        left[i] = inf.readInt(0, n, "l_i");
        inf.readSpace();
        right[i] = inf.readInt(0, n, "r_i");
        inf.readEoln();

        ensuref(left[i] != right[i] || left[i] == 0,
                "node %d has the same nonzero left and right child: %d", i, left[i]);

        for (int child : {left[i], right[i]}) {
            if (child == 0) {
                continue;
            }
            ensuref(child != i, "node %d cannot be its own child", i);
            ensuref(parent[child] == 0,
                    "node %d has multiple parents: %d and %d", child, parent[child], i);
            parent[child] = i;
        }
    }

    ensuref(parent[1] == 0, "root node 1 must not have a parent");

    vector<int> order;
    order.reserve(n);
    vector<int> stack = {1};
    vector<char> seen(n + 1, false);
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        ensuref(!seen[v], "node %d is reachable more than once from the root", v);
        seen[v] = true;
        order.push_back(v);
        if (right[v] != 0) {
            stack.push_back(right[v]);
        }
        if (left[v] != 0) {
            stack.push_back(left[v]);
        }
    }

    ensuref((int)order.size() == n,
            "the child table must describe one rooted tree with all N nodes; reached %d of %d",
            (int)order.size(), n);

    vector<long long> visits(n + 1, 0);
    reverse(order.begin(), order.end());
    for (int v : order) {
        long long total = 1;
        if (left[v] != 0) {
            total = min(VISIT_CAP, total + min(VISIT_CAP, 2 * visits[left[v]]));
        }
        if (right[v] != 0) {
            total = min(VISIT_CAP, total + visits[right[v]]);
        }
        visits[v] = total;
    }

    ensuref(k <= visits[1],
            "K must not exceed the total number of visits: K=%lld, visits=%lld",
            k, visits[1]);

    inf.readEof();
}

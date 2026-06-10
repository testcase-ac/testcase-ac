#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

void fillTree(int node, int left, int right, const vector<long long>& values,
              vector<long long>& tree) {
    if (left > right) {
        return;
    }
    int mid = (left + right) / 2;
    tree[node] = values[mid];
    fillTree(node * 2, left, mid - 1, values, tree);
    fillTree(node * 2 + 1, mid + 1, right, values, tree);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.wnext(5, -2) + 2;
    if (rnd.next(10) == 0) {
        k = rnd.next(6, 9);
    }
    int n = (1 << k) - 1;

    int mode = rnd.next(4);
    long long start;
    long long gap;
    if (mode == 0) {
        start = rnd.next(0, 20);
        gap = rnd.next(1, 4);
    } else if (mode == 1) {
        gap = rnd.next(1, 1000);
        start = rnd.next(0LL, 1000000000LL - gap * n);
    } else if (mode == 2) {
        gap = rnd.next(1, 5);
        start = 1000000000LL - gap * n - rnd.next(0, 20);
    } else {
        gap = rnd.next(1000000LL, 10000000LL);
        start = rnd.next(0LL, 1000000000LL - gap * n);
    }

    vector<long long> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = start + gap * i;
    }

    vector<long long> tree(n + 1);
    fillTree(1, 0, n - 1, values, tree);

    int firstLeaf = 1 << (k - 1);
    int hidden = rnd.next(firstLeaf, n);
    long long hiddenValue = tree[hidden];
    tree[hidden] = -1;

    set<long long> visible;
    for (int i = 1; i <= n; ++i) {
        if (tree[i] != -1) {
            visible.insert(tree[i]);
        }
    }

    vector<long long> candidates;
    if (values.front() > 0) {
        candidates.push_back(rnd.next(0LL, values.front() - 1));
    }
    if (values.back() < 1000000000LL) {
        candidates.push_back(rnd.next(values.back() + 1, 1000000000LL));
    }
    for (int tries = 0; tries < 20; ++tries) {
        int pos = rnd.next(0, n - 1);
        long long lo = values[pos] + 1;
        long long hi = values[pos + 1] - 1;
        if (lo <= hi) {
            candidates.push_back(rnd.next(lo, hi));
        }
    }
    if (!visible.count(hiddenValue)) {
        candidates.push_back(hiddenValue);
    }

    long long x = rnd.any(candidates);
    while (visible.count(x)) {
        x = rnd.next(0LL, 1000000000LL);
    }

    vector<long long> output(tree.begin() + 1, tree.end());
    println(n);
    println(output);
    println(x);

    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else if (mode == 2) {
        n = rnd.next(6, 14);
    } else {
        n = rnd.next(10, 35);
    }

    vector<int> parent(n + 1, 0);
    vector<vector<int>> children(n + 1);

    if (mode == 0) {
        parent[1] = 0;
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = i - 1;
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = 1;
        }
    } else {
        int bias = rnd.next(-3, 3);
        for (int i = 2; i <= n; ++i) {
            parent[i] = rnd.wnext(i - 1, bias) + 1;
        }
    }

    if (mode >= 3 && rnd.next(0, 1)) {
        vector<int> perm(n + 1);
        iota(perm.begin(), perm.end(), 0);
        vector<int> labels;
        for (int i = 2; i <= n; ++i) {
            labels.push_back(i);
        }
        shuffle(labels.begin(), labels.end());
        for (int i = 2; i <= n; ++i) {
            perm[i] = labels[i - 2];
        }

        vector<int> relabeledParent(n + 1, 0);
        for (int i = 2; i <= n; ++i) {
            relabeledParent[perm[i]] = perm[parent[i]];
        }
        parent.swap(relabeledParent);
    }

    for (int i = 2; i <= n; ++i) {
        children[parent[i]].push_back(i);
    }

    vector<int> leaves;
    vector<int> internal;
    for (int i = 1; i <= n; ++i) {
        if (children[i].empty()) {
            leaves.push_back(i);
        } else {
            internal.push_back(i);
        }
    }

    int m = rnd.next(1, min(100, max(8, 3 * n)));
    vector<pair<int, int>> queries;
    queries.reserve(m);

    for (int qi = 0; qi < m; ++qi) {
        int type;
        if (qi % 4 == 0) {
            type = 3;
        } else {
            type = rnd.next(1, 3);
        }

        int employee;
        int targetKind = rnd.next(0, 4);
        if (targetKind == 0) {
            employee = 1;
        } else if (targetKind == 1 && !leaves.empty()) {
            employee = rnd.any(leaves);
        } else if (targetKind <= 3 && !internal.empty()) {
            employee = rnd.any(internal);
        } else {
            employee = rnd.next(1, n);
        }
        queries.emplace_back(type, employee);
    }

    println(n);
    vector<int> parentLine(parent.begin() + 1, parent.end());
    println(parentLine);
    println(m);
    for (auto [type, employee] : queries) {
        println(type, employee);
    }

    return 0;
}

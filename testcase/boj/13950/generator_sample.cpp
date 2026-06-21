#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static vector<int> makeRandomConfig(int n, int mode) {
    vector<int> parent(n + 1, 0);

    if (mode == 0 || n == 1) {
        return parent;
    }

    if (mode == 1) {
        int len = rnd.next(2, n);
        int start = rnd.next(1, n - len + 1);
        for (int child = start; child < start + len - 1; ++child) {
            parent[child] = child + 1;
        }
        return parent;
    }

    vector<int> parents;
    for (int x = 2; x <= n; ++x) {
        parents.push_back(x);
    }
    shuffle(parents.begin(), parents.end());

    int chance = mode == 2 ? rnd.next(20, 45) : rnd.next(55, 90);
    for (int p : parents) {
        if (rnd.next(100) >= chance) {
            continue;
        }

        vector<int> children;
        for (int child = 1; child < p; ++child) {
            if (parent[child] == 0) {
                children.push_back(child);
            }
        }
        if (children.empty()) {
            continue;
        }

        parent[rnd.any(children)] = p;
    }

    return parent;
}

static vector<int> perturbConfig(const vector<int>& base) {
    int n = int(base.size()) - 1;
    vector<int> parent = base;

    int edits = rnd.next(1, max(1, n / 3));
    for (int step = 0; step < edits; ++step) {
        int child = rnd.next(1, n);
        parent[child] = 0;

        if (child == n || rnd.next(100) < 35) {
            continue;
        }

        vector<int> usedParent(n + 1, 0);
        for (int x = 1; x <= n; ++x) {
            if (parent[x] != 0) {
                usedParent[parent[x]] = 1;
            }
        }

        vector<int> choices;
        for (int p = child + 1; p <= n; ++p) {
            if (!usedParent[p]) {
                choices.push_back(p);
            }
        }
        if (!choices.empty()) {
            parent[child] = rnd.any(choices);
        }
    }

    return parent;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 15);
    if (rnd.next(100) < 10) {
        n = rnd.next(16, 30);
    }

    int pMode = rnd.next(0, 3);
    vector<int> p = makeRandomConfig(n, pMode);
    vector<int> q;
    if (rnd.next(100) < 45) {
        q = perturbConfig(p);
    } else {
        q = makeRandomConfig(n, rnd.next(0, 3));
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << p[i];
    }
    cout << '\n';

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << q[i];
    }
    cout << '\n';

    return 0;
}

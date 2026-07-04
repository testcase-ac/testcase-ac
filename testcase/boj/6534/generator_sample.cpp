#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

struct TestCase {
    int n1;
    int n2;
    vector<pair<int, int>> deps;
};

int discOf(int package, int n1) {
    return package <= n1 ? 1 : 2;
}

vector<int> shuffledPackages(int n) {
    vector<int> packages(n);
    iota(packages.begin(), packages.end(), 1);
    shuffle(packages.begin(), packages.end());
    return packages;
}

void addDependency(vector<pair<int, int>>& deps, int x, int y) {
    if (x != y) {
        deps.push_back({x, y});
    }
}

TestCase makeEmptyCase() {
    return {rnd.next(1, 4), rnd.next(1, 4), {}};
}

TestCase makeAlternatingChain() {
    int n1 = rnd.next(2, 6);
    int n2 = rnd.next(2, 6);
    vector<int> disc1;
    vector<int> disc2;
    for (int i = 1; i <= n1; ++i) {
        disc1.push_back(i);
    }
    for (int i = 1; i <= n2; ++i) {
        disc2.push_back(n1 + i);
    }
    shuffle(disc1.begin(), disc1.end());
    shuffle(disc2.begin(), disc2.end());

    vector<int> order;
    int takeDisc = rnd.next(1, 2);
    while (!disc1.empty() || !disc2.empty()) {
        vector<int>& preferred = takeDisc == 1 ? disc1 : disc2;
        vector<int>& other = takeDisc == 1 ? disc2 : disc1;
        if (!preferred.empty()) {
            order.push_back(preferred.back());
            preferred.pop_back();
        } else {
            order.push_back(other.back());
            other.pop_back();
        }
        takeDisc = 3 - takeDisc;
    }

    vector<pair<int, int>> deps;
    for (int i = 1; i < (int)order.size(); ++i) {
        addDependency(deps, order[i], order[i - 1]);
    }
    return {n1, n2, deps};
}

TestCase makeLayeredCase() {
    int n1 = rnd.next(3, 8);
    int n2 = rnd.next(3, 8);
    int n = n1 + n2;
    vector<int> order = shuffledPackages(n);
    int layers = rnd.next(2, 4);
    vector<vector<int>> layer(layers);
    for (int i = 0; i < n; ++i) {
        layer[i * layers / n].push_back(order[i]);
    }

    vector<pair<int, int>> deps;
    for (int upper = 1; upper < layers; ++upper) {
        for (int x : layer[upper]) {
            int attempts = rnd.next(1, min(3, upper * 2));
            for (int attempt = 0; attempt < attempts; ++attempt) {
                int lower = rnd.next(0, upper - 1);
                if (!layer[lower].empty()) {
                    addDependency(deps, x, rnd.any(layer[lower]));
                }
            }
        }
    }
    return {n1, n2, deps};
}

TestCase makeFanCase() {
    int n1 = rnd.next(2, 7);
    int n2 = rnd.next(2, 7);
    int n = n1 + n2;
    vector<int> order = shuffledPackages(n);
    int root = order.front();
    vector<pair<int, int>> deps;

    for (int i = 1; i < n; ++i) {
        if (rnd.next(0, 99) < 70) {
            addDependency(deps, order[i], root);
        }
        if (i >= 2 && rnd.next(0, 99) < 35) {
            addDependency(deps, order[i], order[rnd.next(1, i - 1)]);
        }
    }
    return {n1, n2, deps};
}

TestCase makeRandomDagCase() {
    int n1 = rnd.next(2, 9);
    int n2 = rnd.next(2, 9);
    int n = n1 + n2;
    vector<int> order = shuffledPackages(n);
    int density = rnd.next(15, 45);
    vector<pair<int, int>> deps;

    for (int later = 1; later < n; ++later) {
        for (int earlier = 0; earlier < later; ++earlier) {
            int bonus = discOf(order[later], n1) != discOf(order[earlier], n1) ? 10 : 0;
            if (rnd.next(0, 99) < density + bonus) {
                addDependency(deps, order[later], order[earlier]);
            }
        }
    }
    shuffle(deps.begin(), deps.end());
    return {n1, n2, deps};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<TestCase> cases;
    int targetCases = rnd.next(3, 7);
    for (int i = 0; i < targetCases; ++i) {
        int mode = rnd.next(0, 4);
        if (mode == 0) {
            cases.push_back(makeEmptyCase());
        } else if (mode == 1) {
            cases.push_back(makeAlternatingChain());
        } else if (mode == 2) {
            cases.push_back(makeLayeredCase());
        } else if (mode == 3) {
            cases.push_back(makeFanCase());
        } else {
            cases.push_back(makeRandomDagCase());
        }
    }

    for (const TestCase& tc : cases) {
        println(tc.n1, tc.n2, (int)tc.deps.size());
        for (auto [x, y] : tc.deps) {
            println(x, y);
        }
    }
    println(0, 0, 0);
    return 0;
}

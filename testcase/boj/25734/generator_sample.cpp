#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int pickPresent(const set<int>& active) {
    int index = rnd.next((int)active.size());
    auto it = active.begin();
    advance(it, index);
    return *it;
}

int freshNear(const set<int>& active, int base) {
    for (int radius = 0; radius <= 8; ++radius) {
        vector<int> candidates;
        if (base - radius >= 1 && !active.count(base - radius)) {
            candidates.push_back(base - radius);
        }
        if (radius != 0 && base + radius >= 1 && base + radius <= 1000000000 &&
            !active.count(base + radius)) {
            candidates.push_back(base + radius);
        }
        if (!candidates.empty()) {
            return rnd.any(candidates);
        }
    }

    int x;
    do {
        x = rnd.next(1, 1000000000);
    } while (active.count(x));
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int q = rnd.next(1, 80);
    set<int> active;
    vector<pair<int, int>> operations;

    int clusterBase;
    if (mode == 4) {
        clusterBase = rnd.next(999999920, 1000000000);
    } else if (mode == 5) {
        clusterBase = rnd.next(1, 80);
    } else {
        clusterBase = rnd.next(10, 200);
    }

    for (int i = 0; i < q; ++i) {
        bool insert = active.empty() || rnd.next(100) < 62;
        if (!insert && mode == 2 && active.size() < 4) {
            insert = true;
        }

        if (insert) {
            int x;
            if (mode == 0) {
                x = freshNear(active, clusterBase + rnd.next(-3, 3));
            } else if (mode == 1) {
                x = freshNear(active, clusterBase + rnd.next(-20, 20) * 3);
            } else if (mode == 2) {
                if (active.empty()) {
                    x = freshNear(active, clusterBase);
                } else {
                    x = freshNear(active, pickPresent(active) + rnd.any(vector<int>{-1, 1}));
                }
            } else if (mode == 3) {
                x = freshNear(active, rnd.next(1, 1000000000));
            } else if (mode == 4) {
                x = freshNear(active, clusterBase + rnd.next(-20, 0));
            } else {
                x = freshNear(active, clusterBase + (i % 2 == 0 ? i / 2 : -i / 2));
            }
            active.insert(x);
            operations.push_back({1, x});
        } else {
            int x;
            if (mode == 2 && active.size() >= 3) {
                vector<int> values(active.begin(), active.end());
                x = values[rnd.next(1, (int)values.size() - 2)];
            } else {
                x = pickPresent(active);
            }
            active.erase(x);
            operations.push_back({2, x});
        }
    }

    println((int)operations.size());
    for (auto [op, x] : operations) {
        println(op, x);
    }

    return 0;
}

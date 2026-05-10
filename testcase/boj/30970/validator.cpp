#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Item {
    int q, p, idx;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    vector<Item> items;
    items.reserve(N);

    for (int i = 0; i < N; ++i) {
        int q = inf.readInt(1, 10000, "Q_i");
        inf.readSpace();
        int p = inf.readInt(1, 10000, "P_i");
        inf.readEoln();
        items.push_back({q, p, i});
    }

    // Check that there are no two miniatures with the same (Q, P)
    // i.e., all pairs (Q_i, P_i) are distinct.
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        if (a.q != b.q) return a.q < b.q;
        return a.p < b.p;
    });
    for (int i = 1; i < N; ++i) {
        ensuref(!(items[i].q == items[i-1].q && items[i].p == items[i-1].p),
                "Duplicate miniature found: two items share Q = %d, P = %d",
                items[i].q, items[i].p);
    }

    // Additionally, the story text says "품질과 가격이 전부 동일한 두 촉석루 미니어처는 없었다.",
    // which we interpreted as (Q, P) pairs being unique. It does NOT say
    // Q_i all distinct or P_i all distinct, so those are allowed.

    // Now simulate the two selection methods to ensure they are always well-defined.

    auto simulate_first = [&](const vector<Item>& a) {
        vector<bool> taken(a.size(), false);

        auto pick = [&](int step) -> int {
            int bestIdx = -1;
            for (int i = 0; i < (int)a.size(); ++i) {
                if (taken[i]) continue;
                if (bestIdx == -1) {
                    bestIdx = i;
                    continue;
                }
                // Method 1: max quality, tie -> min price
                if (a[i].q > a[bestIdx].q) {
                    bestIdx = i;
                } else if (a[i].q == a[bestIdx].q && a[i].p < a[bestIdx].p) {
                    bestIdx = i;
                }
            }
            ensuref(bestIdx != -1, "First method: unable to pick item at step %d", step);
            taken[bestIdx] = true;
            return bestIdx;
        };

        int first = pick(1);
        int second = pick(2);
        // Just to keep compiler happy; we don't need the result for validation beyond existence.
        (void)first;
        (void)second;
    };

    auto simulate_second = [&](const vector<Item>& a) {
        vector<bool> taken(a.size(), false);

        auto pick = [&](int step) -> int {
            int bestIdx = -1;
            for (int i = 0; i < (int)a.size(); ++i) {
                if (taken[i]) continue;
                if (bestIdx == -1) {
                    bestIdx = i;
                    continue;
                }
                // Method 2: min price, tie -> max quality
                if (a[i].p < a[bestIdx].p) {
                    bestIdx = i;
                } else if (a[i].p == a[bestIdx].p && a[i].q > a[bestIdx].q) {
                    bestIdx = i;
                }
            }
            ensuref(bestIdx != -1, "Second method: unable to pick item at step %d", step);
            taken[bestIdx] = true;
            return bestIdx;
        };

        int first = pick(1);
        int second = pick(2);
        (void)first;
        (void)second;
    };

    simulate_first(items);
    simulate_second(items);

    inf.readEof();
}

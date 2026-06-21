#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> twoDistinctTargets(int i, int n, const vector<int>& preferred) {
    vector<int> candidates;
    for (int x : preferred) {
        if (x != i && 1 <= x && x <= n &&
            find(candidates.begin(), candidates.end(), x) == candidates.end()) {
            candidates.push_back(x);
        }
    }
    for (int x = 1; x <= n; ++x) {
        if (x != i && find(candidates.begin(), candidates.end(), x) == candidates.end()) {
            candidates.push_back(x);
        }
    }

    int firstIndex = rnd.next((int)candidates.size());
    int first = candidates[firstIndex];
    candidates.erase(candidates.begin() + firstIndex);
    int second = rnd.any(candidates);
    return {first, second};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(3, mode == 3 ? 18 : 12);
    vector<pair<int, int>> ask(n + 1);

    if (mode == 0) {
        vector<int> label(n);
        iota(label.begin(), label.end(), 1);
        shuffle(label.begin(), label.end());

        for (int pos = 0; pos < n; ++pos) {
            int i = label[pos];
            int next = label[(pos + 1) % n];
            int jump = label[(pos + rnd.next(2, n - 1)) % n];
            ask[i] = twoDistinctTargets(i, n, {next, jump});
        }
    } else if (mode == 1) {
        int pivotA = rnd.next(1, n);
        int pivotB = rnd.next(1, n - 1);
        if (pivotB >= pivotA) ++pivotB;

        for (int i = 1; i <= n; ++i) {
            int near = i <= n / 2 ? rnd.next(1, n / 2) : rnd.next(n / 2 + 1, n);
            int cross = i <= n / 2 ? rnd.next(n / 2 + 1, n) : rnd.next(1, n / 2);
            ask[i] = twoDistinctTargets(i, n, {pivotA, pivotB, near, cross});
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            int a = i == n ? 1 : i + 1;
            int b = i + rnd.next(2, n - 1);
            if (b > n) b -= n;
            ask[i] = twoDistinctTargets(i, n, {a, b});
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            ask[i] = twoDistinctTargets(i, n, {});
        }
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (rnd.next(2)) swap(ask[i].first, ask[i].second);
        println(ask[i].first, ask[i].second);
    }

    return 0;
}

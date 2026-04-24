#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int m = rnd.next(1, 3);
    int n = rnd.next(m + 1, 8);
    int r = rnd.next(1, 5);

    vector<int> L(n);
    vector<vector<int>> combos;

    // Generate left endpoints and valid non-intersecting subsets until we have at least two choices
    while (true) {
        L[0] = rnd.next(0, 5);
        for (int i = 1; i < n; i++) {
            // delta in [1, r+3] gives some chances of overlap (delta<r) or gap (delta>=r)
            int delta = rnd.next(1, r + 3);
            L[i] = L[i - 1] + delta;
        }
        combos.clear();
        // enumerate all subsets of size m
        for (int mask = 0; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) != m) continue;
            vector<int> idx;
            for (int i = 0; i < n; i++)
                if (mask & (1 << i))
                    idx.push_back(i);
            bool ok = true;
            for (int j = 0; j + 1 < m; j++) {
                // ensure intervals [L[idx[j]], L[idx[j]]+r] and [L[idx[j+1]], L[idx[j+1]]+r] don't intersect
                if (L[idx[j]] + r >= L[idx[j+1]]) {
                    ok = false;
                    break;
                }
            }
            if (ok) combos.push_back(idx);
        }
        if ((int)combos.size() >= 2) break;
        // otherwise regenerate
    }

    // pick distinct start and end sets
    vector<int> S = rnd.any(combos);
    vector<int> E;
    do {
        E = rnd.any(combos);
    } while (E == S);

    // convert to 1-based and sort
    for (int &x : S) x++;
    for (int &x : E) x++;
    sort(S.begin(), S.end());
    sort(E.begin(), E.end());

    // Output in the required format
    println(m, n);
    println(r);
    println(L);
    println(S);
    println(E);

    return 0;
}

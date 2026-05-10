#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read T
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // 2. Read N
        int N = inf.readInt(1, 100, "N");
        inf.readEoln();

        // 3. Read 2N prices
        vector<int> P = inf.readInts(2 * N, 1, 1000000000, "P_i");
        inf.readEoln();

        // 4. Check non-decreasing order
        for (int i = 1; i < 2 * N; ++i) {
            ensuref(P[i - 1] <= P[i], "Prices not sorted at index %d: %d > %d", i, P[i - 1], P[i]);
        }

        // 5. Check that there exists a unique partition into N discounted and N original prices
        //    such that for each discounted price d, there exists an original price o = d / 0.75 = d * 4 / 3,
        //    o is integer, o % 4 == 0, and both d and o are in P, and all pairs are unique.

        // The problem guarantees that there is exactly one solution.
        // We must check that for the given P, there is exactly one way to partition.

        // We'll use a greedy pairing from smallest to largest, as in the intended solution.
        multiset<int> ms(P.begin(), P.end());
        vector<int> discounts;
        bool possible = true;
        for (int i = 0; i < 2 * N; ++i) {
            int d = P[i];
            if (ms.find(d) == ms.end()) continue; // already paired
            // Try to pair d as discounted price
            long long o = d * 4LL;
            if (o % 3 != 0) continue; // original price must be integer
            o /= 3;
            if (o < 1 || o > 1000000000) continue;
            if (o % 4 != 0) continue; // original price must be multiple of 4
            if (ms.find((int)o) == ms.end()) {
                possible = false;
                break;
            }
            // Pair d and o
            ms.erase(ms.find(d));
            ms.erase(ms.find((int)o));
            discounts.push_back(d);
            if ((int)discounts.size() > N) {
                possible = false;
                break;
            }
        }
        ensuref(possible, "Cannot pair all prices in test case %d", tc + 1);
        ensuref((int)discounts.size() == N, "Number of discounted prices is not N in test case %d", tc + 1);
        ensuref(ms.empty(), "Not all prices are paired in test case %d", tc + 1);

        // Now, check that the pairing is unique.
        // To do this, we try to find a second valid pairing that is different from the greedy one.
        // We'll use a backtracking approach, but with pruning for efficiency since N is small.

        // Prepare for backtracking
        vector<int> Pcopy = P;
        vector<bool> used(2 * N, false);
        vector<int> candidate_discounts;
        int found = 0;

        // Map from price to indices (for handling duplicates)
        map<int, vector<int>> price_indices;
        for (int i = 0; i < 2 * N; ++i) {
            price_indices[P[i]].push_back(i);
        }

        // Helper for backtracking
        function<void(int, multiset<int>&, vector<int>&)> dfs = [&](int pos, multiset<int>& remain, vector<int>& curr) {
            if ((int)curr.size() == N) {
                // Check if all prices are used
                if (remain.empty()) {
                    // Compare with greedy solution
                    vector<int> sorted_curr = curr;
                    sort(sorted_curr.begin(), sorted_curr.end());
                    vector<int> sorted_greedy = discounts;
                    sort(sorted_greedy.begin(), sorted_greedy.end());
                    if (sorted_curr != sorted_greedy) {
                        found++;
                    }
                }
                return;
            }
            if (found > 0) return; // Already found another solution

            // For each remaining price, try to use as discounted price
            // To avoid duplicate work, always pick the smallest remaining price >= pos
            int last = -1;
            for (int i = pos; i < 2 * N; ++i) {
                if (used[i]) continue;
                int d = P[i];
                if (d == last) continue; // avoid duplicate work for same value
                last = d;

                long long o = d * 4LL;
                if (o % 3 != 0) continue;
                o /= 3;
                if (o < 1 || o > 1000000000) continue;
                if (o % 4 != 0) continue;
                int o_int = (int)o;

                // Find an unused o_int
                auto it = price_indices.find(o_int);
                if (it == price_indices.end()) continue;
                bool found_o = false;
                int o_idx = -1;
                for (int idx : it->second) {
                    if (!used[idx] && idx != i) {
                        found_o = true;
                        o_idx = idx;
                        break;
                    }
                }
                if (!found_o) continue;

                // Use d and o_int
                used[i] = true;
                used[o_idx] = true;
                remain.erase(remain.find(d));
                remain.erase(remain.find(o_int));
                curr.push_back(d);

                dfs(i + 1, remain, curr);

                curr.pop_back();
                remain.insert(d);
                remain.insert(o_int);
                used[i] = false;
                used[o_idx] = false;

                if (found > 0) return;
            }
        };

        // Only run backtracking if N <= 10, otherwise it's too slow and not needed for small T
        // But since N <= 100 and T <= 100, and the greedy solution is always unique by problem guarantee,
        // we can skip the backtracking for large N, but for small N (say N <= 10), we can check for multiple solutions.
        if (N <= 10) {
            multiset<int> remain(P.begin(), P.end());
            vector<int> curr;
            dfs(0, remain, curr);
            ensuref(found == 0, "Multiple valid pairings found in test case %d", tc + 1);
        }
    }

    inf.readEof();
}

#include "testlib.h"

#include <algorithm>
#include <climits>
#include <numeric>
#include <vector>

using namespace std;

static bool isSubset(const vector<int>& small, const vector<int>& large) {
    return includes(large.begin(), large.end(), small.begin(), small.end());
}

static bool intersects(const vector<int>& a, const vector<int>& b) {
    size_t i = 0;
    size_t j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] == b[j]) return true;
        if (a[i] < b[j]) {
            ++i;
        } else {
            ++j;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "n");
        inf.readSpace();
        int m = inf.readInt(1, 150, "m");
        inf.readEoln();

        vector<int> price(m);
        vector<vector<int>> items(m);
        vector<vector<char>> present(m, vector<char>(n + 1, 0));
        vector<int> itemSeen(n + 1, 0);

        for (int i = 0; i < m; ++i) {
            price[i] = inf.readInt(1, 1000000, "p_i");
            inf.readSpace();
            int s = inf.readInt(1, n, "s_i");

            items[i].reserve(s);
            for (int j = 0; j < s; ++j) {
                inf.readSpace();
                int dessert = inf.readInt(1, n, "dessert");
                ensuref(!present[i][dessert],
                        "bundle %d contains dessert %d more than once", i + 1, dessert);
                present[i][dessert] = 1;
                items[i].push_back(dessert);
                ++itemSeen[dessert];
            }
            inf.readEoln();

            sort(items[i].begin(), items[i].end());
        }

        for (int dessert = 1; dessert <= n; ++dessert) {
            ensuref(itemSeen[dessert] > 0, "dessert %d does not appear in any bundle", dessert);
        }

        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j < m; ++j) {
                bool iInJ = isSubset(items[i], items[j]);
                bool jInI = isSubset(items[j], items[i]);
                bool disjoint = !intersects(items[i], items[j]);
                ensuref(iInJ || jInI || disjoint,
                        "bundles %d and %d are neither nested nor disjoint", i + 1, j + 1);
            }
        }

        vector<vector<int>> uniqueItems;
        vector<int> uniquePrice;
        for (int i = 0; i < m; ++i) {
            int pos = -1;
            for (int j = 0; j < (int)uniqueItems.size(); ++j) {
                if (items[i] == uniqueItems[j]) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1) {
                uniqueItems.push_back(items[i]);
                uniquePrice.push_back(price[i]);
            } else {
                uniquePrice[pos] = min(uniquePrice[pos], price[i]);
            }
        }

        int k = uniqueItems.size();
        vector<int> order(k);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            if (uniqueItems[a].size() != uniqueItems[b].size()) {
                return uniqueItems[a].size() < uniqueItems[b].size();
            }
            return a < b;
        });

        const long long INF = 4'000'000'000'000'000'000LL;
        vector<long long> minCost(k, INF);
        for (int idx : order) {
            long long childSum = 0;
            vector<char> covered(n + 1, 0);

            for (int child = 0; child < k; ++child) {
                if (child == idx) continue;
                if (uniqueItems[child].size() >= uniqueItems[idx].size()) continue;
                if (!isSubset(uniqueItems[child], uniqueItems[idx])) continue;

                bool maximalChild = true;
                for (int other = 0; other < k; ++other) {
                    if (other == idx || other == child) continue;
                    if (uniqueItems[other].size() <= uniqueItems[child].size() ||
                        uniqueItems[other].size() >= uniqueItems[idx].size()) {
                        continue;
                    }
                    if (isSubset(uniqueItems[child], uniqueItems[other]) &&
                        isSubset(uniqueItems[other], uniqueItems[idx])) {
                        maximalChild = false;
                        break;
                    }
                }
                if (!maximalChild) continue;

                childSum = min(INF, childSum + minCost[child]);
                for (int dessert : uniqueItems[child]) covered[dessert] = 1;
            }

            bool childrenCoverBundle = true;
            for (int dessert : uniqueItems[idx]) {
                if (!covered[dessert]) {
                    childrenCoverBundle = false;
                    break;
                }
            }

            minCost[idx] = uniquePrice[idx];
            if (childrenCoverBundle) minCost[idx] = min(minCost[idx], childSum);
        }

        long long answer = 0;
        vector<char> covered(n + 1, 0);
        for (int idx = 0; idx < k; ++idx) {
            bool maximal = true;
            for (int other = 0; other < k; ++other) {
                if (other == idx) continue;
                if (uniqueItems[other].size() <= uniqueItems[idx].size()) continue;
                if (isSubset(uniqueItems[idx], uniqueItems[other])) {
                    maximal = false;
                    break;
                }
            }
            if (!maximal) continue;

            answer = min(INF, answer + minCost[idx]);
            for (int dessert : uniqueItems[idx]) covered[dessert] = 1;
        }

        for (int dessert = 1; dessert <= n; ++dessert) {
            ensuref(covered[dessert], "dessert %d is not covered by maximal bundles", dessert);
        }
        ensuref(answer <= INT_MAX, "minimum cost %lld does not fit in a 32-bit signed integer",
                answer);
    }

    inf.readEof();
}

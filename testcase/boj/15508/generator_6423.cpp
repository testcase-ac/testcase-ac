#include "testlib.h"
#include <vector>
#include <algorithm>
#include <bitset>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of jars
    int n = rnd.next(2, 20);
    int Kmax = min(n, 10);

    // Generate a random number of connected components (inseparable groups)
    // Ensure at least one component has size >= 2 so that m >= 1
    int compCount = rnd.next(1, max(1, n - 1));

    // Random partition of n into compCount positive parts
    vector<int> separators;
    if (compCount > 1) {
        vector<int> pool;
        for (int i = 1; i < n; i++) pool.push_back(i);
        shuffle(pool.begin(), pool.end());
        separators.assign(pool.begin(), pool.begin() + (compCount - 1));
        sort(separators.begin(), separators.end());
    }
    vector<int> compSize;
    int prev = 0;
    for (int x : separators) {
        compSize.push_back(x - prev);
        prev = x;
    }
    compSize.push_back(n - prev);

    // Compute reachable subset sums of components to know safe ks
    bitset<21> dp;
    dp.reset();
    dp[0] = 1;
    for (int s : compSize) {
        dp |= (dp << s);
    }
    vector<int> possibleK, impossibleK;
    for (int k = 1; k <= Kmax; k++) {
        if (dp[k]) possibleK.push_back(k);
        else impossibleK.push_back(k);
    }

    // Decide if we want a SAFE or DOOMED case
    bool wantSafe = rnd.next(0, 1);
    int k;
    if (wantSafe && !possibleK.empty()) {
        k = rnd.any(possibleK);
    } else if (!wantSafe && !impossibleK.empty()) {
        k = rnd.any(impossibleK);
    } else if (!possibleK.empty()) {
        k = rnd.any(possibleK);
        wantSafe = true;
    } else {
        k = rnd.any(impossibleK);
        wantSafe = false;
    }

    // Assign jars 1..n to components
    vector<int> compOf(n+1);
    int cur = 1;
    for (int i = 0; i < compCount; i++) {
        for (int j = 0; j < compSize[i]; j++) {
            compOf[cur++] = i;
        }
    }

    // Build all possible inseparable pairs within each component
    vector<pair<int,int>> cand;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (compOf[i] == compOf[j]) {
                cand.emplace_back(i, j);
            }
        }
    }
    shuffle(cand.begin(), cand.end());

    // Choose at least one unique pair (m >= 1)
    int maxUnique = min((int)cand.size(), 100);
    int mUnique = rnd.next(1, maxUnique);
    vector<pair<int,int>> edges(cand.begin(), cand.begin() + mUnique);

    // Optionally add some duplicates to catch naive solutions
    int dupCap = min((int)edges.size() / 2, 100 - (int)edges.size());
    int dups = dupCap > 0 ? rnd.next(0, dupCap) : 0;
    for (int i = 0; i < dups; i++) {
        edges.push_back(rnd.any(edges));
    }
    shuffle(edges.begin(), edges.end());
    int m = edges.size();

    // Output the generated test case
    println(n, m, k);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}

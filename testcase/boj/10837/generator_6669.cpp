#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose K: sometimes very small, sometimes moderate (up to 20)
    int K;
    if (rnd.next(0, 9) < 3) {
        K = rnd.next(1, 5);
    } else {
        K = rnd.next(6, 20);
    }

    // Build a set of strategic fixed queries
    vector<pair<int,int>> queries;
    // Always include corners
    queries.emplace_back(0, 0);
    queries.emplace_back(0, K);
    queries.emplace_back(K, 0);
    queries.emplace_back(K, K);
    // Middle area
    int mid = K / 2;
    queries.emplace_back(mid, mid);
    if (mid + 1 <= K) {
        queries.emplace_back(mid, mid + 1);
        queries.emplace_back(mid + 1, mid);
        queries.emplace_back(mid + 1, mid + 1);
    }
    // One-off small offsets
    if (K >= 1) {
        queries.emplace_back(1, 0);
        queries.emplace_back(0, 1);
    }
    if (K >= 2) {
        queries.emplace_back(K-1, K);
        queries.emplace_back(K, K-1);
    }

    // Remove duplicates
    sort(queries.begin(), queries.end());
    queries.erase(unique(queries.begin(), queries.end()), queries.end());

    // Total possible pairs
    int maxPairs = (K + 1) * (K + 1);
    int fixedCnt = (int)queries.size();

    // Decide how many extra random queries to add (up to 20 more)
    int remainSlots = maxPairs - fixedCnt;
    int addMax = remainSlots > 0 ? min(remainSlots, 20) : 0;
    int addCnt = rnd.next(0, addMax);
    int C = fixedCnt + addCnt;

    // Build remaining pairs
    set<pair<int,int>> used(queries.begin(), queries.end());
    vector<pair<int,int>> remain;
    remain.reserve(remainSlots);
    for (int m = 0; m <= K; m++) {
        for (int n = 0; n <= K; n++) {
            pair<int,int> p = {m, n};
            if (!used.count(p)) remain.push_back(p);
        }
    }
    shuffle(remain.begin(), remain.end());
    // Add extra random queries
    for (int i = 0; i < addCnt; i++) {
        queries.push_back(remain[i]);
    }

    // Final shuffle
    shuffle(queries.begin(), queries.end());
    C = rnd.next(1, (int)queries.size());
    queries.resize(C);

    // Output
    println(K);
    println(C);
    for (auto &p : queries) {
        println(p.first, p.second);
    }
    return 0;
}

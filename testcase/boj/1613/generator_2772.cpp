#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of events
    int N = rnd.next(2, 10);

    // A random permutation to serve as a topological ordering
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end());

    // Prepare all possible edges respecting the topo order
    vector<pair<int,int>> cand;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            cand.emplace_back(perm[i], perm[j]);
        }
    }

    // Choose graph construction type
    string gtype = rnd.next("chain|random");
    vector<pair<int,int>> edges;

    if (gtype == "chain") {
        // Always include the chaining edges
        for (int i = 0; i + 1 < N; i++) {
            edges.emplace_back(perm[i], perm[i+1]);
        }
        // Extra edges beyond the chain
        vector<pair<int,int>> extras;
        for (int i = 0; i < N; i++) {
            for (int j = i + 2; j < N; j++) {
                extras.emplace_back(perm[i], perm[j]);
            }
        }
        shuffle(extras.begin(), extras.end());
        int maxExtra = extras.size();
        int t2 = rnd.next(-2, 2);
        int extNum = maxExtra > 0 ? rnd.wnext(maxExtra, t2) : 0;
        // take up to extNum extras
        extNum = min(extNum, maxExtra);
        for (int i = 0; i < extNum; i++) {
            edges.push_back(extras[i]);
        }
    } else {
        // Fully random DAG: take a skewed number of edges from cand
        shuffle(cand.begin(), cand.end());
        int maxAll = cand.size();
        int t1 = rnd.next(-3, 3);
        // ensure at least 1 edge
        int kAll = rnd.wnext(maxAll, t1) + 1;
        kAll = min(kAll, maxAll);
        for (int i = 0; i < kAll; i++) {
            edges.push_back(cand[i]);
        }
    }

    // Final count of known relations
    int k = edges.size();  // guaranteed >=1

    // Generate queries
    int s = rnd.next(1, N);
    set<pair<int,int>> usedQ;
    vector<pair<int,int>> queries;
    while ((int)queries.size() < s) {
        int a = rnd.next(1, N);
        int b = rnd.next(1, N);
        if (a == b) continue;
        if (usedQ.insert({a, b}).second) {
            queries.emplace_back(a, b);
        }
    }

    // Output in required format
    println(N, k);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    println(s);
    for (auto &q : queries) {
        println(q.first, q.second);
    }

    return 0;
}

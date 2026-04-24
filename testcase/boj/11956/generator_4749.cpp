#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: number of initial terms K
    int K = rnd.next(1, 10);
    // Generate initial sequence elements (small numbers)
    vector<long long> a(K);
    for (int i = 0; i < K; i++) {
        // up to 10 bits to keep hand-checkable
        a[i] = rnd.next(0LL, (1LL << 10) - 1);
    }

    // Determine maximum r in queries, ensures some queries go beyond K
    int hi = K + 5;
    if (hi < 10) hi = 10;
    long long maxR = rnd.next((long long)K + 1, (long long)hi);

    // Number of queries Q
    int Q = rnd.next(1, 20);
    vector<pair<long long, long long>> queries;
    queries.reserve(Q);

    // Generate diverse queries
    for (int i = 0; i < Q; i++) {
        int t = rnd.next(0, 3);
        long long l, r;
        if (t == 0) {
            // Single-point query
            r = rnd.next(1LL, maxR);
            l = r;
        } else if (t == 1) {
            // Entirely within the initial K terms
            l = rnd.next(1LL, (long long)K);
            r = rnd.next(l, (long long)K);
        } else if (t == 2) {
            // Crossing the boundary between initial and recursive
            l = rnd.next(1LL, (long long)K);
            r = rnd.next((long long)K + 1, maxR);
        } else {
            // Entirely in the recursive region beyond K
            l = rnd.next((long long)K + 1, maxR);
            r = rnd.next(l, maxR);
        }
        queries.emplace_back(l, r);
    }

    // Output in the required format
    println(K);
    println(a);
    println(Q);
    for (auto &qr : queries) {
        println(qr.first, qr.second);
    }

    return 0;
}

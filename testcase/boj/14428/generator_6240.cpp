#include "testlib.h"
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Size of the sequence
    int N = rnd.next(1, 30);
    // Maximum value for array elements and updates
    int Vmax = rnd.next(10, 1000);

    // Create a small pool of distinct values to induce duplicates
    int K = rnd.next(1, min(N, 10));
    set<int> pool;
    while ((int)pool.size() < K) {
        pool.insert(rnd.next(1, Vmax));
    }
    vector<int> vals(pool.begin(), pool.end());

    // Build initial array with possible duplicates
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.any(vals);
    }

    // Number of queries
    int M = rnd.next(1, 2 * N);
    vector<tuple<int,int,int>> queries;
    bool hasType2 = false;
    // Probability of range query
    double ratio = rnd.next() * 0.6 + 0.2; // in [0.2,0.8]

    for (int q = 0; q < M; q++) {
        if (rnd.next() < ratio) {
            // Type 2 query: range minimum query
            int l, r;
            if (rnd.next() < 0.5) {
                l = rnd.next(1, N);
                r = rnd.next(l, N);
            } else {
                // biased towards small ranges
                int len = rnd.wnext(N, -1);
                int maxL = N - len;
                if (maxL < 1) maxL = 1;
                l = rnd.next(1, maxL);
                r = l + len;
            }
            queries.emplace_back(2, l, r);
            hasType2 = true;
        } else {
            // Type 1 query: point update
            int idx = rnd.next(1, N);
            int v = rnd.next(1, Vmax);
            queries.emplace_back(1, idx, v);
        }
    }
    // Ensure at least one type-2 query
    if (!hasType2) {
        int pos = rnd.next(0, M-1);
        int l = rnd.next(1, N);
        int r = rnd.next(l, N);
        queries[pos] = make_tuple(2, l, r);
    }

    // Output
    println(N);
    println(A);
    println(M);
    for (auto &t : queries) {
        int tp, x, y;
        tie(tp, x, y) = t;
        println(tp, x, y);
    }

    return 0;
}

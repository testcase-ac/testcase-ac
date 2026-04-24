#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small n and q
    int N = rnd.next(1, 10);
    int Q = rnd.next(1, 20);

    // Hyper-parameter: number of distinct student IDs (bias to be small)
    int maxDistinct = min(N, 5);
    int D = rnd.wnext(maxDistinct, -1) + 1;  // in [1..maxDistinct]

    // Hyper-parameter: maximum possible ID
    int id_max = rnd.next(D, 1000000);

    // Pick D unique IDs
    set<int> s;
    while ((int)s.size() < D) {
        s.insert(rnd.next(1, id_max));
    }
    vector<int> ids(s.begin(), s.end());
    shuffle(ids.begin(), ids.end());

    // Build the daily best-student list with some bias
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        double p = rnd.next();
        if (p < 0.2) {
            // frequent winner
            A[i] = ids[0];
        } else {
            // any of the distinct IDs
            A[i] = rnd.any(ids);
        }
    }

    // Output n, q and the list
    println(N, Q);
    println(A);

    // Generate queries with diversity: single-day, full-range, random-range
    for (int i = 0; i < Q; i++) {
        double p = rnd.next();
        int l, r;
        if (p < 0.2) {
            // single-day query
            l = r = rnd.next(1, N);
        } else if (p < 0.5) {
            // full-range query
            l = 1;
            r = N;
        } else {
            // random sub-range
            l = rnd.next(1, N);
            r = rnd.next(l, N);
        }
        println(l, r);
    }

    return 0;
}

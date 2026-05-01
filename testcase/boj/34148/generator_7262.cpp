#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Select scenario for diversity
    int scenario = rnd.next(0, 3);
    int N, K;
    if (scenario == 0) {
        // minimal edge case
        N = 1;
        K = 1;
    } else if (scenario == 1) {
        // small sizes
        N = rnd.next(2, 5);
        int maxIntervals = N * (N + 1) / 2;
        K = rnd.next(1, min(maxIntervals, 5));
    } else if (scenario == 2) {
        // medium sizes
        N = rnd.next(6, 15);
        int maxIntervals = N * (N + 1) / 2;
        K = rnd.next(1, min(maxIntervals, 20));
    } else {
        // larger medium
        N = rnd.next(16, 30);
        int maxIntervals = N * (N + 1) / 2;
        K = rnd.next(1, min(maxIntervals, 30));
    }
    // Generate initial binary sequence with varying density
    double oneProb = rnd.next(0.0, 1.0);
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = (rnd.next() < oneProb ? 1 : 0);
    }
    // Generate K queries with overlap, duplicates, various lengths
    vector<pair<int,int>> segs;
    double dupProb = rnd.next(0.0, 1.0);
    for (int i = 0; i < K; i++) {
        if (i > 0 && rnd.next() < dupProb) {
            // duplicate a previous interval
            int j = rnd.next(0, (int)segs.size() - 1);
            segs.push_back(segs[j]);
        } else {
            // new interval with varied length
            double t = rnd.next();
            int len;
            if (t < 0.2) {
                len = 1;
            } else if (t < 0.6) {
                len = rnd.next(1, min(N, 5));
            } else {
                len = rnd.next(1, N);
            }
            int l = rnd.next(1, N - len + 1);
            int r = l + len - 1;
            segs.emplace_back(l, r);
        }
    }
    // Optionally reorder queries
    if (rnd.next() < 0.5) {
        shuffle(segs.begin(), segs.end());
    }
    // Output
    println(N, K);
    println(A);
    for (auto &pr : segs) {
        println(pr.first, pr.second);
    }
    return 0;
}

#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size parameters
    int N = rnd.next(3, 10);

    // Choose number of colors, sometimes less than N/2, sometimes up to 2*N
    int C;
    if (rnd.next(0, 1) == 0) {
        C = rnd.next(1, max(1, N/2));
    } else {
        C = rnd.next(1, N * 2);
    }

    // Decide if we inject a global bias color
    bool useBias = rnd.next(0, 1) == 1;
    int biasColor = useBias ? rnd.next(1, C) : -1;
    double biasProb = useBias ? rnd.next(30, 70) / 100.0 : 0.0;

    // Generate the sequence of hat colors
    vector<int> hats(N);
    for (int i = 0; i < N; i++) {
        if (useBias && rnd.next() < biasProb) {
            hats[i] = biasColor;
        } else {
            // pick any color (possibly biasColor) to increase noise
            hats[i] = rnd.next(1, C);
        }
    }

    // Number of queries
    int M = rnd.next(1, min(20, N*(N-1)/2));

    // Build queries with varied lengths: short, medium, long
    vector<pair<int,int>> queries;
    for (int i = 0; i < M; i++) {
        double mode = rnd.next();
        int lo, hi;
        if (mode < 0.3) {
            // short segments
            lo = 1; hi = min(3, N);
        } else if (mode < 0.6) {
            // medium
            lo = 1; hi = max(1, N/2);
        } else {
            // long
            lo = max(1, N/2);
            hi = N;
        }
        int len = rnd.next(lo, hi);
        int A = rnd.next(1, N - len + 1);
        int B = A + len - 1;
        queries.emplace_back(A, B);
    }

    // Output
    println(N, C);
    println(hats);
    println(M);
    for (auto &q : queries) {
        println(q.first, q.second);
    }
    return 0;
}

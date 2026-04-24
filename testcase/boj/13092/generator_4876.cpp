#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small N
    int N = rnd.next(2, 10);
    // Compute minimum K so that 2^K >= N
    int minK = 0;
    int pow2 = 1;
    while (pow2 < N) {
        pow2 <<= 1;
        minK++;
    }
    // Allow some extra height but keep small
    int extra = rnd.next(0, 3);
    int K = min(minK + extra, 50);

    // Generate strengths with several modes for diversity
    vector<int> A(N);
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        // Uniform random strengths
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(1, 100000);
        }
    } else if (mode == 1) {
        // Few clusters
        int C = rnd.next(1, min(N, 4));
        vector<int> centers(C);
        for (int i = 0; i < C; i++) {
            centers[i] = rnd.next(1, 100000);
        }
        for (int i = 0; i < N; i++) {
            int c = rnd.next(0, C - 1);
            int delta = rnd.next(-10000, 10000);
            int v = centers[c] + delta;
            if (v < 1) v = 1;
            if (v > 100000) v = 100000;
            A[i] = v;
        }
    } else {
        // Evenly spaced progression
        int maxStep = N > 1 ? 1000 : 0;
        int step = rnd.next(0, maxStep);
        int maxBase = max(1, 100000 - step * (N - 1));
        int base = rnd.next(1, maxBase);
        for (int i = 0; i < N; i++) {
            A[i] = base + i * step;
        }
    }

    // Randomize order or sort for diversity
    int ord = rnd.next(0, 2);
    if (ord == 0) {
        // keep random
    } else if (ord == 1) {
        sort(A.begin(), A.end());
    } else {
        sort(A.begin(), A.end(), greater<int>());
    }

    // Output
    println(N, K);
    println(A);

    return 0;
}

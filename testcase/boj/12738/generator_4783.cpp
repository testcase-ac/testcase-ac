#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sequence length hyper-parameter
    int N = rnd.next(1, 10);
    vector<int> A(N);

    // Choose step magnitude from a small set for diversity
    vector<int> stepOptions = {1, 5, 10, 20};
    int maxStep = rnd.any(stepOptions);

    // Four sequence patterns: uniform, increasing, decreasing, zigzag
    int type = rnd.next(0, 3);
    // Initial value for incremental types
    int cur = rnd.next(-maxStep * N, maxStep * N);

    if (type == 0) {
        // Uniform random over a symmetric range
        int lo = -maxStep * N;
        int hi =  maxStep * N;
        for (int i = 0; i < N; ++i) {
            A[i] = rnd.next(lo, hi);
        }
    } else if (type == 1) {
        // Mostly increasing
        for (int i = 0; i < N; ++i) {
            int d = rnd.next(0, maxStep);
            cur += d;
            A[i] = cur;
        }
    } else if (type == 2) {
        // Mostly decreasing
        for (int i = 0; i < N; ++i) {
            int d = rnd.next(0, maxStep);
            cur -= d;
            A[i] = cur;
        }
    } else {
        // Zigzag pattern
        for (int i = 0; i < N; ++i) {
            int d = rnd.next(0, maxStep);
            if (i % 2 == 0) cur += d;
            else          cur -= d;
            A[i] = cur;
        }
    }

    // Inject some duplicates for additional edge cases
    double dupProb = rnd.next() * 0.5;  // up to 50% chance
    for (int i = 0; i < N; ++i) {
        if (rnd.next() < dupProb && N > 1) {
            int j = rnd.next(0, N - 1);
            A[i] = A[j];
        }
    }

    // Output
    println(N);
    println(A);

    return 0;
}

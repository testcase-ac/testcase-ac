#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(1, 8);
    int N;
    vector<int> A;

    if (type == 1) {
        // N = 1, simple edge case
        N = 1;
        A.assign(1, rnd.next(1, 20));
    } else if (type == 2) {
        // Very small random
        N = rnd.next(2, 5);
        A.resize(N);
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1, 20);
    } else if (type == 3) {
        // Strictly (or mostly) decreasing sequence
        N = rnd.next(5, 15);
        A.resize(N);
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1, 30);
        sort(A.rbegin(), A.rend());
        // Ensure not all equal
        if (A.front() == A.back()) A[0] += 5;
    } else if (type == 4) {
        // Strictly (or mostly) increasing sequence
        N = rnd.next(5, 15);
        A.resize(N);
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1, 30);
        sort(A.begin(), A.end());
        if (A.front() == A.back()) A.back() += 5;
    } else if (type == 5) {
        // Zig-zag high/low pattern
        N = rnd.next(10, 25);
        A.resize(N);
        int lowBase = rnd.next(1, 5);
        int highBase = rnd.next(15, 30);
        for (int i = 0; i < N; ++i) {
            if (i % 2 == 0)
                A[i] = highBase + rnd.next(0, 3);
            else
                A[i] = lowBase + rnd.next(0, 3);
        }
    } else if (type == 6) {
        // Last element is (one of) the minima, others mostly larger
        N = rnd.next(5, 20);
        A.resize(N);
        int minVal = rnd.next(1, 5);
        for (int i = 0; i < N - 1; ++i) {
            A[i] = rnd.next(minVal + 1, minVal + 15);
        }
        A[N - 1] = minVal;
        // Optionally insert some additional minima in the middle
        int extraMins = rnd.next(0, N / 3);
        for (int k = 0; k < extraMins; ++k) {
            int pos = rnd.next(0, N - 2);
            A[pos] = minVal;
        }
    } else if (type == 7) {
        // Medium random small values
        N = rnd.next(10, 30);
        A.resize(N);
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1, 25);
    } else { // type == 8
        // Larger N and mixed value scales (including near upper bound)
        N = rnd.next(25, 40);
        A.resize(N);
        int baseLarge = rnd.next(900000, 999000);
        for (int i = 0; i < N; ++i) {
            if (i % 3 == 0) {
                A[i] = baseLarge + rnd.next(0, 1000); // up to ~1e6
                if (A[i] > 1000000) A[i] = 1000000;
            } else if (i % 3 == 1) {
                A[i] = rnd.next(1, 50);
            } else {
                A[i] = rnd.next(1000, 100000);
            }
        }
        // Randomly decide if last is small or large
        if (rnd.next(0, 1) == 0)
            A[N - 1] = rnd.next(1, 50);
        else
            A[N - 1] = baseLarge;
    }

    println(N);
    println(A);

    return 0;
}

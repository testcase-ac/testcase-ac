#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of students
    int N = rnd.next(1, 12);

    // Cap for raw scores
    int maxA = rnd.next(0, 1)
               ? rnd.next(0, 100000)
               : rnd.next(0, 100);

    // Distribution type for A
    int distType = rnd.next(0, 3);
    vector<int> A(N);
    if (distType == 0) {
        // Uniform
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(0, maxA);
    } else if (distType == 1) {
        // Skewed low
        for (int i = 0; i < N; i++)
            A[i] = rnd.wnext(maxA + 1, -rnd.next(1, 3));
    } else if (distType == 2) {
        // Skewed high
        for (int i = 0; i < N; i++)
            A[i] = rnd.wnext(maxA + 1, rnd.next(1, 3));
    } else {
        // Two clusters
        if (N >= 2) {
            int split = rnd.next(1, N - 1);
            for (int i = 0; i < split; i++)
                A[i] = rnd.next(0, maxA / 3);
            for (int i = split; i < N; i++)
                A[i] = rnd.next(maxA * 2 / 3, maxA);
        } else {
            A[0] = rnd.next(0, maxA);
        }
    }
    shuffle(A.begin(), A.end());

    // Teacher parameters p, q, r
    int p = rnd.next(1, 4999);
    int q = rnd.next(1, 4999);
    int min_r = p + q;
    if (min_r > 9999) min_r = 9999;
    int r = rnd.next(min_r, 9999);

    // Compute sum of original scores
    int64_t sumA = 0;
    for (int x : A) sumA += x;

    // Target S
    int SType = rnd.next(0, 2);
    int S;
    if (SType == 0) {
        // Around typical sum
        int low = int(max<int64_t>(1, sumA / 2));
        int high = int(sumA + int64_t(N) * max(p, q) + 100);
        if (low > high) high = low;
        S = rnd.next(low, high);
    } else if (SType == 1) {
        // Too large
        int low = int(sumA + 1);
        int high = int(sumA + int64_t(N) * max(p, q) + 500);
        if (low > high) high = low;
        S = rnd.next(low, high);
    } else {
        // Too small
        int high = int(max<int64_t>(1, sumA / 3));
        S = rnd.next(1, high);
    }

    // Output
    println(N);
    println(A);
    println(p, q, r, S);

    return 0;
}

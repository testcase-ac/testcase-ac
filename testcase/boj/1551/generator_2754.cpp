#include "testlib.h"
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small sequence size
    int N = rnd.next(1, 10);
    int K = (N == 1 ? 0 : rnd.next(0, N - 1));

    // Hyper-parameter: bound for values
    vector<int> bounds = {10, 20, 50, 100};
    int bound = rnd.any(bounds);

    // Decide a pattern for diversity
    double p = rnd.next();
    vector<int> A(N);

    if (N >= 2 && p < 0.25) {
        // Arithmetic progression within [-100,100]
        int start = rnd.next(-bound, bound);
        int maxDiff = (100 - abs(start)) / (N - 1);
        int diff = (maxDiff > 0 ? rnd.next(-maxDiff, maxDiff) : 0);
        for (int i = 0; i < N; i++)
            A[i] = start + diff * i;
    } else if (p < 0.5) {
        // All equal
        int v = rnd.next(-bound, bound);
        for (int i = 0; i < N; i++)
            A[i] = v;
    } else if (p < 0.75) {
        // Zigzag between two values
        int v1 = rnd.next(-bound, bound);
        int v2 = rnd.next(-bound, bound);
        for (int i = 0; i < N; i++)
            A[i] = (i % 2 ? v1 : v2);
    } else {
        // Completely random
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(-bound, bound);
    }

    // Output
    println(N, K);
    for (int i = 0; i < N; i++) {
        if (i) printf(",");
        printf("%d", A[i]);
    }
    printf("\n");
    return 0;
}

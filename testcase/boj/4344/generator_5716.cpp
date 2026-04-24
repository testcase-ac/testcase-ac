#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int C = rnd.next(3, 7);
    println(C);
    for (int i = 0; i < C; i++) {
        // Choose N with mix of sizes and edge-cases
        double rd = rnd.next();
        int N;
        if (rd < 0.2) {
            N = 1;
        } else if (rd < 0.4) {
            N = rnd.next(2, 3);
        } else if (rd < 0.8) {
            N = rnd.next(4, 20);
        } else {
            N = rnd.next(21, 50);
        }
        vector<int> a(N);
        // Choose score distribution
        double td = rnd.next();
        if (td < 0.25) {
            // uniform 0..100
            for (int j = 0; j < N; j++)
                a[j] = rnd.next(0, 100);
        } else if (td < 0.5) {
            // skew-low: more high scores
            int lo = rnd.next(50, 100);
            for (int j = 0; j < N; j++)
                a[j] = rnd.next(lo, 100);
        } else if (td < 0.75) {
            // skew-high: more low scores
            int hi = rnd.next(0, 50);
            for (int j = 0; j < N; j++)
                a[j] = rnd.next(0, hi);
        } else {
            // bi-modal: half low (0..10), half high (90..100)
            int half = N / 2;
            for (int j = 0; j < half; j++)
                a[j] = rnd.next(0, 10);
            for (int j = half; j < N; j++)
                a[j] = rnd.next(90, 100);
        }
        shuffle(a.begin(), a.end());
        // Output this test case
        printf("%d", N);
        for (int x : a)
            printf(" %d", x);
        if (i + 1 < C) printf("\n");
    }
    return 0;
}

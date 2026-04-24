#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of classes
    int K = rnd.next(1, 10);
    println(K);

    for (int ci = 0; ci < K; ++ci) {
        // Number of students in this class
        int N = rnd.next(2, 10);

        // Choose a score distribution pattern: low, mid, or high ranges
        int pattern = rnd.next(0, 2);
        int lo, hi;
        if (pattern == 0) {
            // Mostly low scores
            lo = 0;
            hi = rnd.next(10, 30);
        } else if (pattern == 1) {
            // Mid-range scores
            lo = rnd.next(20, 50);
            hi = rnd.next(50, 80);
        } else {
            // Mostly high scores
            lo = rnd.next(70, 90);
            hi = 100;
        }

        // Generate scores
        vector<int> scores(N);
        for (int i = 0; i < N; ++i) {
            scores[i] = rnd.next(lo, hi);
        }

        // Introduce some duplicates randomly
        if (rnd.next() < 0.5) {
            int dups = rnd.next(1, N / 2);
            for (int d = 0; d < dups; ++d) {
                int p1 = rnd.next(0, N-1);
                int p2 = rnd.next(0, N-1);
                scores[p1] = scores[p2];
            }
        }

        // Shuffle the score order
        shuffle(scores.begin(), scores.end());

        // Output this class
        printf("%d", N);
        for (int x : scores) {
            printf(" %d", x);
        }
        printf("\n");
    }

    return 0;
}

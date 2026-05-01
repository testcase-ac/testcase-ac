#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(2, 5);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        // Bias K sometimes small, sometimes large
        int tBias = rnd.next(0, 1) ? 1 : -1;
        // Generate K in [3..15], biased by tBias
        int K = rnd.wnext(13, tBias) + 3;

        // Choose distribution type for chapter sizes
        int dist = rnd.next(0, 3);
        vector<int> a(K);

        if (dist == 0) {
            // Uniform random small sizes
            for (int i = 0; i < K; i++) {
                a[i] = rnd.next(1, 100);
            }
        } else if (dist == 1) {
            // Ascending sequence with small increments
            int cur = rnd.next(1, 10);
            for (int i = 0; i < K; i++) {
                cur += rnd.next(0, 10);
                a[i] = cur;
            }
        } else if (dist == 2) {
            // Descending sequence with moderate increments
            int cur = rnd.next(100, 200);
            for (int i = 0; i < K; i++) {
                cur += rnd.next(0, 20);
                a[i] = cur;
            }
            reverse(a.begin(), a.end());
        } else {
            // Mixed extremes: half small, half large, then shuffle
            for (int i = 0; i < K; i++) {
                if (i < K/2) a[i] = rnd.next(1, 10);
                else         a[i] = rnd.next(1000, 10000);
            }
            shuffle(a.begin(), a.end());
        }

        // Output this test case
        println(K);
        println(a);
    }

    return 0;
}

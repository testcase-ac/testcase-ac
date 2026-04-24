#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 3);
    for (int t = 0; t < T; t++) {
        int type = rnd.next(0, 4);
        int n;
        vector<long long> h;
        if (type == 0) {
            // Random heights, n biased small
            n = rnd.wnext(20, -2) + 1;  // [1,20], bias small
            h.resize(n);
            for (int i = 0; i < n; i++)
                h[i] = rnd.next(0, 20);
        } else if (type == 1) {
            // All equal heights
            n = rnd.next(1, 15);
            long long val = rnd.next(0, 20);
            h.assign(n, val);
        } else if (type == 2) {
            // Strictly increasing
            n = rnd.next(1, 15);
            int base = rnd.next(0, 5);
            h.resize(n);
            for (int i = 0; i < n; i++)
                h[i] = base + i;
        } else if (type == 3) {
            // Strictly decreasing
            n = rnd.next(1, 15);
            int base = rnd.next(n - 1, n + 10);
            h.resize(n);
            for (int i = 0; i < n; i++)
                h[i] = base - i;
        } else {
            // Many zeros mixed with random
            n = rnd.next(1, 15);
            h.resize(n);
            for (int i = 0; i < n; i++) {
                if (rnd.next() < 0.5) h[i] = 0;
                else h[i] = rnd.next(1, 20);
            }
        }
        // Print this test case
        printf("%d", n);
        for (auto x : h)
            printf(" %lld", x);
        printf("\n");
    }
    // End marker
    printf("0\n");
    return 0;
}

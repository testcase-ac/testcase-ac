#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases (will end with a 0)
    int T = rnd.next(1, 5);
    for (int tc = 0; tc < T; ++tc) {
        // Sequence length
        int n = rnd.next(1, 10);
        println(n);
        // Choose a pattern type for diversity
        int tp = rnd.next(0, 5);
        vector<int> A(n);
        if (tp == 0) {
            // Fully random 1..100
            for (int i = 0; i < n; ++i)
                A[i] = rnd.next(1, 100);
        } else if (tp == 1) {
            // Random small values 1..20
            for (int i = 0; i < n; ++i)
                A[i] = rnd.next(1, 20);
        } else if (tp == 2) {
            // Constant array
            int v = rnd.next(1, 100);
            for (int i = 0; i < n; ++i)
                A[i] = v;
        } else if (tp == 3) {
            // Alternating two distinct values
            int v1 = rnd.next(1, 100);
            int v2;
            do { v2 = rnd.next(1, 100); } while (v2 == v1);
            for (int i = 0; i < n; ++i)
                A[i] = (i % 2 == 0 ? v1 : v2);
        } else if (tp == 4) {
            // Increasing pattern
            int cur = rnd.next(1, 50);
            for (int i = 0; i < n; ++i) {
                A[i] = cur;
                cur = min(100, cur + rnd.next(0, 5));
            }
        } else {
            // Decreasing pattern
            int cur = rnd.next(n, 100);
            for (int i = 0; i < n; ++i) {
                A[i] = cur;
                cur = max(1, cur - rnd.next(0, 5));
            }
        }
        // Output sequence elements, one per line
        for (int x : A)
            println(x);
    }
    // End marker
    println(0);
    return 0;
}

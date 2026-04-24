#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small but varied
    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        // Hyper-parameter for N: sometimes small, sometimes larger
        int N;
        if (rnd.next() < 0.5)
            N = rnd.next(1, 5);
        else
            N = rnd.next(6, 20);
        println(N);

        // Maximum value for this test case
        int maxv = rnd.next(1, 10);
        // Choose distribution mode: uniform, skew-high, skew-low
        int mode = rnd.next(0, 2);

        vector<int> a(N);
        for (int i = 0; i < N; i++) {
            if (mode == 0) {
                // uniform from 1 to maxv
                a[i] = rnd.next(1, maxv);
            } else if (mode == 1) {
                // weighted toward higher values
                a[i] = rnd.wnext(maxv, 2) + 1;
            } else {
                // weighted toward lower values
                a[i] = rnd.wnext(maxv, -2) + 1;
            }
        }

        // Shuffle to avoid any accidental ordering patterns
        shuffle(a.begin(), a.end());
        println(a);
    }

    return 0;
}

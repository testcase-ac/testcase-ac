#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    for (int i = 0; i < T; i++) {
        // Sequence length n between 1 and 10
        int n = rnd.next(1, 10);

        // Choose a type for k to ensure diversity:
        // 0: k in [0, n-1]
        // 1: k in [n, min(100, n+20)]
        // 2: k = n-1 (max adjacent)
        // 3: k = 0 (no adjacent 1s)
        int type = rnd.next(0, 3);
        int k;
        if (type == 0) {
            k = rnd.next(0, n - 1);
        } else if (type == 1) {
            int hi = min(100, n + rnd.next(1, 20));
            k = rnd.next(n, hi);
        } else if (type == 2) {
            k = n - 1;
        } else {
            k = 0;
        }

        println(n, k);
    }

    return 0;
}

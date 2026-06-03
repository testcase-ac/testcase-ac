#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_A = 2000000000;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = {
        2, 3, 5, 7, 11, 17, 31, 97, 257, 65537,
        999983, 1000000007, 1999999943, 1999999973
    };

    int n = rnd.next(0, 2);
    int m = rnd.any(primes);

    vector<int> anchors = {
        1,
        2,
        max(1, m - 1),
        m,
        min(MAX_A, m + 1),
        MAX_A - rnd.next(0, 20),
        rnd.next(1, 100),
        rnd.next(1, MAX_A)
    };

    vector<int> a(n + 1);
    int mode = rnd.next(0, 5);
    for (int i = 0; i <= n; ++i) {
        if (mode == 0) {
            a[i] = rnd.any(anchors);
        } else if (mode == 1) {
            a[i] = (i % 2 == 0 ? rnd.next(1, 20) : MAX_A - rnd.next(0, 1000));
        } else if (mode == 2) {
            a[i] = min(MAX_A, m + rnd.next(0, 10));
        } else if (mode == 3) {
            a[i] = rnd.next(1, 1000);
        } else if (mode == 4) {
            a[i] = (rnd.next(0, 1) ? 1 : MAX_A);
        } else {
            a[i] = rnd.next(1, MAX_A);
        }
    }

    println(n);
    println(a);
    println(m);

    return 0;
}

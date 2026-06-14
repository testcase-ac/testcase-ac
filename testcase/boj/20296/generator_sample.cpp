#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n, m, M, K;
    int mode = rnd.next(8);

    if (mode == 0) {
        n = rnd.next(2, 12);
        m = rnd.next(0, 20);
        M = m;
        K = n * m;
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        m = rnd.next(0, 20);
        M = rnd.next(m, 30);
        K = n * m;
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        m = rnd.next(0, 20);
        M = rnd.next(m, 30);
        K = n * M;
    } else if (mode == 3) {
        n = rnd.next(2, 18);
        m = rnd.next(0, 10);
        M = rnd.next(m, 18);
        K = rnd.next(n * m, n * M);
    } else if (mode == 4) {
        n = rnd.next(2, 8);
        m = rnd.next(0, 4);
        M = rnd.next(max(m, 1), 8);
        int extra = rnd.next(0, min(n * (M - m), n + 2));
        K = n * m + extra;
    } else if (mode == 5) {
        n = rnd.next(2, 8);
        m = rnd.next(0, 4);
        M = rnd.next(max(m, 1), 8);
        int missing = rnd.next(0, min(n * (M - m), n + 2));
        K = n * M - missing;
    } else if (mode == 6) {
        n = rnd.next(800, 1000);
        m = rnd.next(0, 1000);
        M = rnd.next(m, 1000);
        K = rnd.next(n * m, n * M);
    } else {
        n = rnd.next(2, 1000);
        m = rnd.next(0, 1000);
        M = rnd.next(m, 1000);
        K = rnd.next(n * m, n * M);
    }

    println(n, m, M, K);
    return 0;
}

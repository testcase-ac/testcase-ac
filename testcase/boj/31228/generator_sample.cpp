#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000000;
    int n = 2;
    int k = 1;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        n = rnd.next(2, 30);
        k = rnd.next(1, n - 1);
    } else if (mode == 1) {
        n = rnd.next(900000000, maxN);
        k = rnd.any(vector<int>{1, 2, 3, n - 3, n - 2, n - 1});
        k = max(1, min(k, n - 1));
    } else if (mode == 2) {
        int reducedN = rnd.next(2, 2000);
        int reducedK = rnd.next(1, reducedN - 1);
        int scale = rnd.next(2, maxN / reducedN);
        n = reducedN * scale;
        k = reducedK * scale;
    } else if (mode == 3) {
        n = rnd.next(2, 200000);
        do {
            k = rnd.next(1, n - 1);
        } while (gcd(n, k) != 1);
    } else if (mode == 4) {
        n = rnd.next(2, 500000000) * 2;
        int delta = rnd.next(0, min(1000, n / 2 - 1));
        k = n / 2 - delta;
        if (k < 1) k = 1;
    } else if (mode == 5) {
        n = rnd.next(3, 1000000);
        k = n - rnd.next(1, min(1000, n - 1));
    } else {
        n = rnd.next(2, maxN);
        k = rnd.next(1, n - 1);
    }

    println(n, k);
    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = 1000000000000000000LL;

    int mode = rnd.next(0, 5);
    long long n;
    int k;

    if (mode == 0) {
        n = rnd.next(1LL, 8LL);
        k = rnd.next(0, 3);
    } else if (mode == 1) {
        n = rnd.next(1LL, 30LL);
        k = rnd.next(0, 10);
    } else if (mode == 2) {
        k = rnd.next(1, 10);
        long long q = rnd.next(1LL, 12LL);
        n = q * k + rnd.next(0, k - 1);
    } else if (mode == 3) {
        vector<int> specialK = {0, 1, 2, 9, 10};
        k = rnd.any(specialK);
        n = rnd.next(1LL, 1000LL);
    } else if (mode == 4) {
        n = MAX_N - rnd.next(0LL, 1000LL);
        k = rnd.next(0, 10);
    } else {
        k = rnd.next(1, 10);
        long long q = rnd.next(10000000000000000LL, 100000000000000000LL);
        n = min(MAX_N, q * k + rnd.next(0, k - 1));
    }

    println(n, k);
    return 0;
}

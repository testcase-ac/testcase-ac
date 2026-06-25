#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = 1000000000000000000LL;

    int mode = rnd.next(0, 6);
    long long n;
    long long k;

    if (mode == 0) {
        n = 2;
        k = 1;
    } else if (mode == 1) {
        n = rnd.next(3LL, 20LL);
        k = rnd.next(1LL, n - 1);
    } else if (mode == 2) {
        n = rnd.next(3LL, 100LL);
        k = rnd.any(vector<long long>{1LL, 2LL, n - 2, n - 1});
    } else if (mode == 3) {
        n = rnd.next(1000LL, 1000000LL);
        k = rnd.next(1LL, n - 1);
    } else if (mode == 4) {
        n = rnd.next(MAX_N - 1000, MAX_N);
        k = rnd.any(vector<long long>{1LL, 2LL, n / 2, n - 2, n - 1});
    } else {
        n = rnd.any(vector<long long>{10LL, 100LL, 1000000000LL, MAX_N});
        k = rnd.next(1LL, n - 1);
    }

    k = max(1LL, min(k, n - 1));
    println(n, k);
    return 0;
}

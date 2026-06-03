#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_VALUE = 1000000000000000000LL;
    vector<long long> edgeValues = {1LL, 2LL, 3LL, 10LL, MAX_VALUE - 2, MAX_VALUE - 1, MAX_VALUE};

    long long n;
    long long r;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(1LL, 20LL);
        r = rnd.next(1LL, 20LL);
    } else if (mode == 1) {
        n = rnd.any(edgeValues);
        r = rnd.any(edgeValues);
    } else if (mode == 2) {
        n = rnd.next(1LL, 1000LL);
        r = rnd.next(MAX_VALUE - 1000, MAX_VALUE);
    } else if (mode == 3) {
        n = rnd.next(MAX_VALUE - 1000, MAX_VALUE);
        r = rnd.next(1LL, 1000LL);
    } else if (mode == 4) {
        long long base = rnd.next(1LL, 1000000000LL);
        n = base * rnd.next(1LL, 1000000000LL);
        r = min(MAX_VALUE, n + rnd.next(0LL, 1000000LL));
    } else {
        n = rnd.next(1LL, MAX_VALUE);
        r = rnd.next(1LL, MAX_VALUE);
    }

    println(n, r);

    return 0;
}

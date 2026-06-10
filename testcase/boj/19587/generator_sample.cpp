#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 1000000000000000000LL;
    int mode = rnd.next(0, 5);
    long long n;

    if (mode == 0) {
        n = rnd.next(1LL, 12LL);
    } else if (mode == 1) {
        vector<long long> anchors = {1, 2, 3, 4, 5, 10, 20, 50};
        long long base = rnd.any(anchors);
        long long delta = rnd.next(-2LL, 2LL);
        n = max(1LL, min(maxN, base + delta));
    } else if (mode == 2) {
        n = rnd.next(13LL, 1000000LL);
    } else if (mode == 3) {
        int exponent = rnd.next(1, 59);
        long long base = 1LL << exponent;
        long long delta = rnd.next(-10LL, 10LL);
        n = max(1LL, min(maxN, base + delta));
    } else if (mode == 4) {
        long long prefix = rnd.next(1LL, 1000000000LL);
        long long suffix = rnd.next(0LL, 999999999LL);
        n = min(maxN, prefix * 1000000000LL + suffix);
    } else {
        n = maxN - rnd.next(0LL, 1000000LL);
    }

    println(n);
    return 0;
}

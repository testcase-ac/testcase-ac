#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long limit = 1000000000000LL;
    long long m;

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        m = rnd.next(1LL, 500LL);
    } else if (mode == 1) {
        long long k = rnd.next(1LL, 1000000LL);
        long long delta = rnd.next(-5LL, 5LL);
        m = k * k + delta;
    } else if (mode == 2) {
        long long k = rnd.next(1LL, 707106LL);
        long long delta = rnd.next(-5LL, 5LL);
        m = 2LL * k * k + delta;
    } else if (mode == 3) {
        long long width = rnd.next(0LL, 1000000LL);
        m = limit - width;
    } else {
        long long hi = rnd.next(1LL, limit);
        m = rnd.next(1LL, hi);
    }

    m = max(1LL, min(limit, m));
    println(m);

    return 0;
}

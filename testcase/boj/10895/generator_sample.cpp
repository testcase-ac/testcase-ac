#include "testlib.h"

#include <vector>

using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const ll MAX_VALUE = 1000000000LL;
    int mode = rnd.next(0, 7);
    ll a = 1;
    ll k = 0;

    if (mode == 0) {
        a = 1;
        k = rnd.next(0LL, MAX_VALUE);
    } else if (mode == 1) {
        a = rnd.next(1LL, 30LL);
        k = 0;
    } else if (mode == 2) {
        a = rnd.next(2LL, 30LL);
        k = rnd.next(1LL, 8LL);
    } else if (mode == 3) {
        a = rnd.next(2LL, 1000LL);
        k = rnd.any(std::vector<ll>{1LL, 2LL, 3LL, 10LL, 100LL, 1000LL});
    } else if (mode == 4) {
        a = rnd.next(MAX_VALUE - 1000LL, MAX_VALUE);
        k = rnd.next(0LL, 1000LL);
    } else if (mode == 5) {
        a = rnd.any(std::vector<ll>{
            2LL, 3LL, 4LL, 8LL, 16LL, 31LL, 63LL, 127LL,
            255LL, 1023LL, 65535LL, 999999937LL, MAX_VALUE
        });
        k = rnd.next(1LL, MAX_VALUE);
    } else if (mode == 6) {
        a = rnd.next(2LL, MAX_VALUE);
        k = rnd.next(MAX_VALUE - 1000LL, MAX_VALUE);
    } else {
        a = rnd.next(1LL, MAX_VALUE);
        k = rnd.next(0LL, MAX_VALUE);
    }

    println(a, k);
    return 0;
}

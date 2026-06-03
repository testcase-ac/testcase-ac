#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long kMaxA = 1000000000000000000LL;
    long long a;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        a = rnd.next(2LL, 5000LL);
    } else if (mode == 1) {
        long long side = rnd.next(1LL, 1000000LL);
        long long delta = rnd.next(-3LL, 3LL);
        a = side * side + delta;
        a = max(1LL, min(kMaxA, a));
    } else if (mode == 2) {
        long long side = rnd.next(999999000LL, 1000000000LL);
        long long delta = rnd.next(-1000LL, 0LL);
        a = side * side + delta;
        a = max(1LL, min(kMaxA, a));
    } else if (mode == 3) {
        long long scale = rnd.any(vector<long long>{
            1000000LL,
            1000000000LL,
            1000000000000LL,
            1000000000000000LL,
            kMaxA,
        });
        a = rnd.next(max(1LL, scale / 10), scale);
    } else if (mode == 4) {
        a = kMaxA - rnd.next(0LL, 1000000LL);
    } else {
        a = rnd.next(1LL, kMaxA);
    }

    println(a);
    return 0;
}

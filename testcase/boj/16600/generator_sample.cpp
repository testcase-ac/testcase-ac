#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long kMaxA = 1000000000000000000LL;
    long long a = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        a = rnd.next(1LL, 200LL);
    } else if (mode == 1) {
        a = rnd.next(1LL, kMaxA);
    } else if (mode == 2) {
        long long side = rnd.next(1LL, 1000000000LL);
        a = side * side;
    } else if (mode == 3) {
        long long side = rnd.next(1LL, 1000000000LL);
        long long base = side * side;
        long long delta = rnd.next(-1000000LL, 1000000LL);
        a = max(1LL, min(kMaxA, base + delta));
    } else if (mode == 4) {
        int exponent = rnd.next(0, 18);
        a = 1;
        for (int i = 0; i < exponent; ++i) a *= 10;
    } else {
        a = rnd.next(kMaxA - 1000000LL, kMaxA);
    }

    println(a);
    return 0;
}

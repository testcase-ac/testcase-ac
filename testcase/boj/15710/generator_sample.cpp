#include "testlib.h"
#include <vector>

using namespace std;

long long randomCard() {
    long long high = rnd.next(0, (1 << 15) - 1);
    long long low = rnd.next(0, (1 << 16) - 1);
    return (high << 16) | low;
}

long long randomN() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(2, 10);
    if (mode == 2) return rnd.next(11, 1000);
    if (mode == 3) return rnd.next(100000000LL, 1000000000LL);
    return rnd.next(1LL, 1000000000LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    constexpr long long MAX_CARD = (1LL << 31) - 1;
    vector<long long> interesting = {
        0,
        1,
        2,
        3,
        7,
        (1LL << 15) - 1,
        1LL << 15,
        (1LL << 30) - 1,
        1LL << 30,
        MAX_CARD,
    };

    long long a;
    long long b;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        a = rnd.any(interesting);
        b = a;
    } else if (mode == 1) {
        a = rnd.any(interesting);
        b = rnd.any(interesting);
    } else if (mode == 2) {
        a = rnd.next(0, 1024);
        b = rnd.next(0, 1024);
    } else if (mode == 3) {
        a = MAX_CARD - rnd.next(0, 1024);
        b = MAX_CARD - rnd.next(0, 1024);
    } else if (mode == 4) {
        a = randomCard();
        b = a ^ rnd.any(interesting);
    } else {
        a = randomCard();
        b = randomCard();
    }

    println(a, b, randomN());
    return 0;
}

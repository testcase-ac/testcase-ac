#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampN(long long value) {
    return static_cast<int>(max(1LL, min(1000000LL, value)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> powers2;
    for (int x = 1; x <= 1000000; x *= 2) powers2.push_back(x);

    vector<int> powers3;
    for (int x = 1; x <= 1000000; x *= 3) powers3.push_back(x);

    int mode = rnd.next(0, 5);
    int n = 1;

    if (mode == 0) {
        n = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(999000, 1000000);
    } else if (mode == 2) {
        int base = rnd.any(powers2);
        n = clampN(base + rnd.next(-8, 8));
    } else if (mode == 3) {
        int base = rnd.any(powers3);
        n = clampN(base + rnd.next(-8, 8));
    } else if (mode == 4) {
        long long value = 1;
        int twos = rnd.next(0, 18);
        int threes = rnd.next(0, 12);
        for (int i = 0; i < twos && value <= 1000000; ++i) value *= 2;
        for (int i = 0; i < threes && value <= 1000000; ++i) value *= 3;
        n = clampN(value + rnd.next(-20, 20));
    } else {
        n = rnd.next(1, 1000000);
    }

    println(n);
    return 0;
}

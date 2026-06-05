#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 1000000;
    vector<int> powers;
    for (int base = 2; base <= 1000; ++base) {
        long long value = 1LL * base * base;
        while (value <= MAX_N) {
            powers.push_back((int)value);
            value *= base;
        }
    }
    sort(powers.begin(), powers.end());
    powers.erase(unique(powers.begin(), powers.end()), powers.end());

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 30);
    } else if (mode == 1) {
        int pivot = rnd.any(powers);
        n = max(1, min(MAX_N, pivot + rnd.next(-3, 3)));
    } else if (mode == 2) {
        n = rnd.next(31, 5000);
    } else if (mode == 3) {
        n = rnd.next(5001, 100000);
    } else if (mode == 4) {
        n = rnd.next(100001, MAX_N);
    } else {
        n = MAX_N - rnd.wnext(10000, -3);
    }

    println(n);
    return 0;
}

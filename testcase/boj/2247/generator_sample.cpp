#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 200000000;
    int mode = rnd.next(0, 7);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 30);
    } else if (mode == 1) {
        int base = rnd.next(2, 20000);
        int delta = rnd.next(-3, 3);
        long long value = 1LL * base * base + delta;
        n = (int)max(1LL, min(1LL * MAX_N, value));
    } else if (mode == 2) {
        int q = rnd.next(2, 20000);
        int value = MAX_N / q;
        n = rnd.next(max(1, value - 5), min(MAX_N, value + 5));
    } else if (mode == 3) {
        int factor = rnd.next(2, 1000);
        int multiplier = rnd.next(1, min(200000, MAX_N / factor));
        n = factor * multiplier;
    } else if (mode == 4) {
        vector<int> powers;
        for (long long value = 1; value <= MAX_N; value *= 2) powers.push_back((int)value);
        for (long long value = 3; value <= MAX_N; value *= 3) powers.push_back((int)value);
        n = rnd.any(powers);
        n = rnd.next(max(1, n - 2), min(MAX_N, n + 2));
    } else if (mode == 5) {
        n = rnd.next(MAX_N - 1000000, MAX_N);
    } else {
        n = rnd.next(1, MAX_N);
    }

    println(n);
    return 0;
}

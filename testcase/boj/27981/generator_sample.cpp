#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = 1000000000000000LL;

    vector<long long> anchors = {
        1LL,
        2LL,
        3LL,
        4LL,
        7LL,
        8LL,
        15LL,
        16LL,
        31LL,
        32LL,
        63LL,
        64LL,
        127LL,
        128LL,
        255LL,
        256LL,
        511LL,
        512LL,
        1023LL,
        1024LL,
        MAX_N
    };

    long long value = 1;
    for (int bit = 12; bit <= 49; bit += rnd.next(3, 7)) {
        long long p = 1LL << bit;
        anchors.push_back(p - 1);
        anchors.push_back(p);
        anchors.push_back(min(MAX_N, p + rnd.next(0LL, min(1000000LL, MAX_N - p))));
    }

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        value = rnd.next(1LL, 300LL);
    } else if (mode == 1) {
        long long base = rnd.any(anchors);
        long long delta = rnd.next(-5LL, 5LL);
        value = min(MAX_N, max(1LL, base + delta));
    } else if (mode == 2) {
        value = rnd.next(1LL, 1000000LL);
    } else if (mode == 3) {
        long long span = rnd.next(0LL, 1000000000000LL);
        value = MAX_N - span;
    } else if (mode == 4) {
        int bit = rnd.next(0, 49);
        long long high = min(MAX_N, (1LL << bit) + rnd.next(0LL, (1LL << min(bit, 20))));
        value = rnd.next(max(1LL, high / 2), high);
    } else {
        value = rnd.next(1LL, MAX_N);
    }

    vector<int> kAnchors = {1, 2, 3, 4, 5, 7, 10, 20, 30, 40, 49, 50};
    int kMode = rnd.next(0, 3);
    int k;
    if (kMode == 0) {
        k = rnd.any(kAnchors);
    } else if (kMode == 1) {
        k = rnd.next(1, 10);
    } else if (kMode == 2) {
        k = rnd.next(40, 50);
    } else {
        k = rnd.next(1, 50);
    }

    println(value, k);
    return 0;
}

#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const long long MAX_K = 1000000000LL;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<long long> socks;

    if (mode == 0) {
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) socks.push_back(rnd.next(1, 6));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        long long base = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) socks.push_back(base + rnd.next(0, 3));
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        long long otherSum = 0;
        for (int i = 1; i < n; ++i) {
            long long value = rnd.next(1, 1000);
            socks.push_back(value);
            otherSum += value;
        }
        socks.push_back(min(MAX_K, otherSum + rnd.next(1, 1000)));
    } else if (mode == 3) {
        n = rnd.next(3, 30);
        long long otherSum = 0;
        for (int i = 1; i < n; ++i) {
            long long value = rnd.next(1, 1000000);
            socks.push_back(value);
            otherSum += value;
        }
        socks.push_back(max(1LL, otherSum + rnd.next(-5, 5)));
    } else if (mode == 4) {
        n = rnd.next(2, 80);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) socks.push_back(rnd.next(999999900, 1000000000));
            else socks.push_back(rnd.next(1, 1000000));
        }
    } else {
        n = rnd.next(900, 1000);
        for (int i = 0; i < n; ++i) socks.push_back(rnd.next(1, 1000));
    }

    shuffle(socks.begin(), socks.end());

    println(n);
    for (long long value : socks) println(value);

    return 0;
}

#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000LL;
    const int MAX_M = 100000;

    long long s = 1;
    long long f = 1;
    int m = 1;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        s = rnd.next(1, 12);
        f = rnd.next(1, 12);
        m = rnd.next(1, 120);
    } else if (mode == 1) {
        s = rnd.next(1, 1000);
        f = rnd.next(1, 1000);
        vector<int> choices = {1, 2, 3, 4, 5, 6, 10, 12, 20, 30, 60, 97, 99991, MAX_M};
        m = rnd.any(choices);
    } else if (mode == 2) {
        s = rnd.next(1, 30);
        f = rnd.next(100000000LL, LIMIT);
        if (rnd.next(2)) swap(s, f);
        m = rnd.next(2, MAX_M);
    } else if (mode == 3) {
        s = rnd.next(900000000LL, LIMIT);
        f = rnd.next(900000000LL, LIMIT);
        m = rnd.next(90000, MAX_M);
    } else if (mode == 4) {
        long long n = rnd.next(2, 2000000);
        s = rnd.next(1LL, n - 1);
        f = n - s;
        vector<int> choices = {64, 128, 256, 512, 1024, 4096, 8192, 32768, 65536};
        m = rnd.any(choices);
    } else if (mode == 5) {
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 31, 97, 997, 99991};
        int p = rnd.any(primes);
        s = rnd.next(1, 200000);
        f = rnd.next(1, 200000);
        m = max(1, min(MAX_M, p + rnd.next(-3, 3)));
    } else {
        s = rnd.next(1LL, LIMIT);
        f = rnd.next(1LL, LIMIT);
        m = rnd.next(1, MAX_M);
    }

    println(s, f, m);
    return 0;
}

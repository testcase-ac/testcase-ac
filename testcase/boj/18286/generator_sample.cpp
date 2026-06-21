#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 1000000000000000000LL;
    int mode = rnd.next(0, 5);
    long long n;

    if (mode == 0) {
        n = rnd.next(1LL, 8LL);
    } else if (mode == 1) {
        n = rnd.next(9LL, 200LL);
    } else if (mode == 2) {
        n = rnd.next(201LL, 1000000LL);
    } else if (mode == 3) {
        vector<long long> bases = {
            1024LL,
            32768LL,
            1048576LL,
            1073741824LL,
            1099511627776LL,
            1125899906842624LL
        };
        long long base = rnd.any(bases);
        long long delta = rnd.next(-5LL, 5LL);
        n = min(maxN, max(1LL, base + delta));
    } else if (mode == 4) {
        n = rnd.next(1000000000000LL, 1000000000000000LL);
    } else {
        n = maxN - rnd.next(0LL, 1000LL);
    }

    int m;
    if (rnd.next(0, 3) == 0) {
        m = rnd.next(1, 5);
    } else {
        vector<int> favoredM = {1, 2, 3, 5};
        m = rnd.any(favoredM);
    }

    println(n, m);
    return 0;
}

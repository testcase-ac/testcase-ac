#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 2147483647;
    const vector<int> primes = {2, 3, 5, 7, 11};

    int a = rnd.any(primes);
    int mode = rnd.next(0, 5);
    int n = 0;

    if (mode == 0) {
        n = rnd.next(0, 25);
    } else if (mode == 1) {
        n = rnd.next(0, 1000);
    } else if (mode == 2) {
        vector<int> powers;
        long long p = a;
        while (p <= maxN) {
            powers.push_back(static_cast<int>(p));
            p *= a;
        }

        int center = rnd.any(powers);
        int delta = rnd.next(-3, 3);
        n = static_cast<int>(min<long long>(maxN, max<long long>(0, static_cast<long long>(center) + delta)));
    } else if (mode == 3) {
        n = maxN - rnd.next(0, 1000);
    } else if (mode == 4) {
        int limit = rnd.wnext(maxN, -6);
        n = rnd.next(0, limit);
    } else {
        n = rnd.next(0, maxN);
    }

    println(n, a);
    return 0;
}

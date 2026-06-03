#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = rnd.next(1, mode == 5 ? 80 : 24);
    vector<long long> rpm(m + 1, 1);

    if (mode == 0) {
        for (int i = 1; i <= m; ++i) rpm[i] = 1;
    } else if (mode == 1) {
        for (int i = 1; i <= m; ++i) rpm[i] = rnd.next(1, 12);
    } else if (mode == 2) {
        vector<long long> factors = {1, 2, 3, 5, 7, 10, 11, 13, 17, 19};
        for (int i = 1; i <= m; ++i) {
            long long next = rpm[i - 1] * rnd.any(factors);
            if (next > 1000000000LL) next = rnd.next(1, 1000);
            rpm[i] = next;
        }
    } else if (mode == 3) {
        for (int i = 1; i <= m; ++i) {
            long long prev = rpm[i - 1];
            vector<long long> divisors;
            for (long long d = 1; d * d <= prev; ++d) {
                if (prev % d == 0) {
                    divisors.push_back(d);
                    if (d * d != prev) divisors.push_back(prev / d);
                }
            }
            rpm[i] = rnd.any(divisors);
        }
    } else if (mode == 4) {
        rpm[0] = 1;
        for (int i = 1; i <= m; ++i) {
            if (i % 3 == 1) {
                rpm[i] = rnd.next(100000000, 1000000000);
            } else if (i % 3 == 2) {
                rpm[i] = rnd.next(1, 20);
            } else {
                rpm[i] = rnd.next(900000000, 1000000000);
            }
        }
    } else {
        for (int i = 1; i <= m; ++i) rpm[i] = rnd.next(1, 100);
    }

    println(m);
    for (int i = 1; i <= m; ++i) {
        long long g = gcd(rpm[i - 1], rpm[i]);
        long long a = rpm[i - 1] / g;
        long long b = rpm[i] / g;
        int s = rnd.next(0, 1);
        println(a, b, s);
    }

    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(8, 30);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        long long a, b, c;
        int mode = rnd.next(0, 6);

        if (mode == 0) {
            long long g = rnd.next(1, 20);
            long long x = rnd.next(1, 40);
            long long y = rnd.next(1, 40);
            a = g * x;
            b = g * y;
            c = g * rnd.next(1LL, max(x, y));
        } else if (mode == 1) {
            long long g = rnd.next(2, 30);
            long long x = rnd.next(1, 30);
            long long y = rnd.next(1, 30);
            a = g * x;
            b = g * y;
            c = g * rnd.next(1LL, max(x, y)) - rnd.next(1LL, g - 1);
            if (c < 1) c += g;
        } else if (mode == 2) {
            a = rnd.next(1, 200);
            b = rnd.next(1, 200);
            c = max(a, b) + rnd.next(1, 100);
        } else if (mode == 3) {
            a = b = rnd.next(1, 1000);
            c = rnd.next(1LL, min(1000000000LL, a + rnd.next(0, 5)));
        } else if (mode == 4) {
            long long g = rnd.next(1, 1000000);
            long long x = rnd.next(1, 1000);
            long long y = rnd.next(1, 1000);
            a = min(1000000000LL, g * x);
            b = min(1000000000LL, g * y);
            long long d = gcd(a, b);
            c = d * rnd.next(1LL, max(a, b) / d);
        } else if (mode == 5) {
            vector<long long> values = {1, 2, 3, 999999937, 1000000000};
            a = rnd.any(values);
            b = rnd.any(values);
            c = rnd.any(values);
        } else {
            a = rnd.next(1, 1000000000);
            b = rnd.next(1, 1000000000);
            c = rnd.next(1, 1000000000);
        }

        println(a, b, c);
    }

    return 0;
}

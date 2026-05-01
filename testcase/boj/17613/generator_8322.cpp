#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 10);
    println(T);
    for (int i = 0; i < T; i++) {
        int tp = rnd.next(0, 3);
        int x, y;
        if (tp == 0) {
            // single point
            if (rnd.next(0, 1) == 0)
                x = rnd.next(1, 100);
            else
                x = rnd.next(1000000000 - 1000, 1000000000);
            y = x;
        } else if (tp == 1) {
            // small range
            int len = rnd.next(1, 30);
            bool tail = rnd.next(0, 1);
            int low = tail ? 1000000000 - 1000 : 1;
            int highb = tail ? 1000000000 - len + 1 : 1000 - len + 1;
            x = rnd.next(low, highb);
            y = x + len - 1;
        } else if (tp == 2) {
            // around a power of two
            int k = rnd.next(0, 29);
            int base = 1 << k;
            int d1 = rnd.next(-10, 10);
            int d2 = rnd.next(-10, 10);
            int l0 = base + min(d1, d2);
            int r0 = base + max(d1, d2);
            long long l = max(1LL, (long long)l0);
            long long r = min(1000000000LL, (long long)r0);
            if (r < l) r = l;
            x = l;
            y = r;
        } else {
            // large range
            int len = rnd.next(1000000, 100000000);
            x = rnd.next(1, 1000000000 - len);
            y = x + len;
        }
        println(x, y);
    }
    return 0;
}

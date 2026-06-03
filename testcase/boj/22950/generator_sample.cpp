#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 40);
    if (rnd.next(0, 9) == 0) n = rnd.next(41, 200);

    string m(n, '0');
    int k = 0;

    if (mode == 0) {
        k = 0;
        for (int i = 0; i < n; ++i) m[i] = char('0' + rnd.next(0, 1));
    } else if (mode == 1) {
        k = rnd.next(1, n);
        for (int i = 0; i < n - k; ++i) m[i] = char('0' + rnd.next(0, 1));
    } else if (mode == 2) {
        k = rnd.next(1, n);
        for (int i = 0; i < n; ++i) m[i] = char('0' + rnd.next(0, 1));
        m[n - rnd.next(1, k)] = '1';
    } else if (mode == 3) {
        k = rnd.next(n, 1000000);
    } else if (mode == 4) {
        k = rnd.next(n, 1000000);
        int ones = rnd.next(1, min(n, 8));
        for (int i = 0; i < ones; ++i) m[rnd.next(0, n - 1)] = '1';
    } else if (mode == 5) {
        k = rnd.next(1, n);
        int trailingZeros = rnd.next(0, k - 1);
        for (int i = 0; i < n; ++i) m[i] = char('0' + rnd.next(0, 1));
        for (int i = 0; i < trailingZeros; ++i) m[n - 1 - i] = '0';
        m[n - 1 - trailingZeros] = '1';
    } else if (mode == 6) {
        k = rnd.next(1, n);
        int extraZeros = rnd.next(0, n - k);
        for (int i = 0; i < n - k - extraZeros; ++i) m[i] = char('0' + rnd.next(0, 1));
        if (n - k - extraZeros > 0 && rnd.next(0, 1)) m[n - k - extraZeros - 1] = '1';
    } else {
        n = 1;
        m = string(n, '0');
        k = rnd.next(0, 1) ? 0 : rnd.next(1, 1000000);
        m[0] = char('0' + rnd.next(0, 1));
    }

    println(n);
    println(m);
    println(k);

    return 0;
}

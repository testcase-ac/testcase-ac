#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode <= 5) {
        n = rnd.next(2, 40);
    } else {
        n = rnd.next(41, 200);
    }

    string x(n, '0');
    x[0] = '1';

    if (mode == 0) {
        // Powers of two trigger no odd operation after the leading bit.
    } else if (mode == 1) {
        fill(x.begin(), x.end(), '1');
    } else if (mode == 2) {
        for (int i = 1; i < n; ++i) {
            x[i] = (i % 2 == rnd.next(0, 1)) ? '1' : '0';
        }
    } else if (mode == 3) {
        int ones = rnd.next(1, min(n - 1, 8));
        for (int i = 0; i < ones; ++i) {
            x[rnd.next(1, n - 1)] = '1';
        }
    } else if (mode == 4) {
        int zeros = rnd.next(1, min(n - 1, 8));
        fill(x.begin(), x.end(), '1');
        for (int i = 0; i < zeros; ++i) {
            x[rnd.next(1, n - 1)] = '0';
        }
    } else if (mode == 5) {
        int suffix = rnd.next(1, n - 1);
        for (int i = 1; i < n - suffix; ++i) {
            x[i] = char('0' + rnd.next(0, 1));
        }
        fill(x.end() - suffix, x.end(), '1');
    } else {
        double oneProbability = rnd.next(0.15, 0.85);
        for (int i = 1; i < n; ++i) {
            x[i] = (rnd.next() < oneProbability) ? '1' : '0';
        }
    }

    println(n);
    println(x);

    return 0;
}

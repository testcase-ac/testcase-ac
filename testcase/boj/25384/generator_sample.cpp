#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    vector<int> c;

    if (mode == 0) {
        n = rnd.next(2, 12);
        c.resize(n);
        for (int i = 0; i < n; ++i) c[i] = i + 1;
        shuffle(c.begin(), c.end());
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        int value = rnd.next(1, 3000);
        c.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        c.resize(n);
        int alphabet = rnd.next(1, min(6, n));
        for (int i = 0; i < n; ++i) c[i] = rnd.next(1, alphabet);
        int pos = rnd.next(0, n - 2);
        c[pos + 1] = c[pos];
    } else if (mode == 3) {
        n = rnd.next(3, 25);
        c.resize(n);
        int a = rnd.next(1, 3000);
        int b = rnd.next(1, 2999);
        if (b >= a) ++b;
        for (int i = 0; i < n; ++i) c[i] = (i % 2 == 0 ? a : b);
    } else if (mode == 4) {
        n = rnd.next(4, 30);
        c.resize(n);
        int low = rnd.next(1, 20);
        int high = rnd.next(2980, 3000);
        for (int i = 0; i < n; ++i) {
            c[i] = rnd.next(0, 1) ? rnd.next(low, min(3000, low + 8)) : rnd.next(max(1, high - 8), high);
        }
    } else if (mode == 5) {
        n = rnd.next(6, 40);
        c.resize(n);
        int alphabet = rnd.next(2, 10);
        for (int i = 0; i < n; ++i) c[i] = rnd.next(1, alphabet);
        for (int i = 1; i < n; ++i) {
            if (c[i] == c[i - 1]) c[i] = c[i] % alphabet + 1;
        }
    } else if (mode == 6) {
        n = rnd.next(2, 60);
        c.resize(n);
        for (int i = 0; i < n; ++i) c[i] = rnd.next(1, 3000);
    } else {
        n = rnd.next(2, 3000);
        c.resize(n);
        int alphabet = rnd.next(1, 3000);
        for (int i = 0; i < n; ++i) c[i] = rnd.next(1, alphabet);
    }

    println(n);
    println(c);

    return 0;
}

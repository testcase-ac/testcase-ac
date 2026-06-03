#include "testlib.h"

#include <vector>
using namespace std;

long long pickValue() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return 0;
    if (mode == 1) return 1;
    if (mode == 2) return 1000000000LL;
    if (mode == 3) return rnd.next(0, 1000);
    return rnd.next(0LL, 1000000000LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int i = 0; i < t; ++i) {
        long long a = pickValue();
        long long b = pickValue();

        int mode = rnd.next(0, 5);
        int c;
        int d;
        if (mode == 0) {
            c = rnd.next(1, 6);
            d = rnd.next(1, 12);
        } else if (mode == 1) {
            c = 1;
            d = rnd.next(1, 100000000);
        } else if (mode == 2) {
            c = 100;
            d = rnd.next(1, 1000000);
        } else if (mode == 3) {
            c = rnd.next(1, 100);
            d = 100000000 / c;
        } else if (mode == 4) {
            c = rnd.next(1, 100);
            d = rnd.next(1, max(1, 1000 / c));
        } else {
            c = rnd.next(1, 100);
            d = rnd.next(1, 100000000 / c);
        }

        println(a, b, c, d);
    }

    return 0;
}

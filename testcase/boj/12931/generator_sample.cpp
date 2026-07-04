#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> b;

    if (mode == 0) {
        n = rnd.next(1, 8);
        b.assign(n, 0);
        int nonzero = rnd.next(1, n);
        for (int i = 0; i < nonzero; ++i) b[i] = rnd.next(0, 3);
        shuffle(b.begin(), b.end());
    } else if (mode == 1) {
        n = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            int exponent = rnd.next(0, 9);
            b.push_back(1 << exponent);
        }
    } else if (mode == 2) {
        n = rnd.next(1, 12);
        int upper = rnd.next(8, 64);
        for (int i = 0; i < n; ++i) b.push_back(rnd.next(0, upper));
    } else if (mode == 3) {
        n = rnd.next(8, 20);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(0, 992);
            if (rnd.next(0, 3) == 0) x |= rnd.next(0, 7);
            b.push_back(x);
        }
    } else if (mode == 4) {
        n = rnd.next(40, 50);
        for (int i = 0; i < n; ++i) b.push_back(rnd.next(0, 1000));
    } else {
        n = rnd.next(1, 50);
        vector<int> interesting = {0, 1, 2, 3, 7, 8, 15, 16, 31, 32, 63, 64, 127, 128, 255, 256, 511, 512, 999, 1000};
        for (int i = 0; i < n; ++i) b.push_back(rnd.any(interesting));
    }

    println(n);
    println(b);
    return 0;
}

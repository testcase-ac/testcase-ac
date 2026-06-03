#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    string k;

    if (mode == 0) {
        n = 1;
        k = "1";
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        k = "1" + string(n - 1, '0');
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        k = string(n, '1');
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        k = "1";
        for (int i = 1; i < n; ++i) k += char('0' + (i % 2));
    } else if (mode == 4) {
        n = rnd.next(2, 80);
        int ones = rnd.next(1, n);
        k = string(n, '0');
        k[0] = '1';
        --ones;
        for (int i = 1; i < n && ones > 0; ++i) {
            int remaining = n - i;
            if (rnd.next(remaining) < ones) {
                k[i] = '1';
                --ones;
            }
        }
    } else {
        n = rnd.next(2, 120);
        k = "1";
        double oneProb = rnd.next(0.05, 0.95);
        for (int i = 1; i < n; ++i) k += (rnd.next() < oneProb ? '1' : '0');
    }

    println(n);
    println(k);

    return 0;
}

#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 30);
    if (mode == 6) n = rnd.next(31, 200);
    if (mode == 7) n = rnd.next(200, 500);

    string x;

    if (mode == 0) {
        x = string(1, char('1' + rnd.next(0, 8)));
    } else if (mode == 1) {
        x = string(n, '9');
        int changes = rnd.next(0, min(n, 5));
        for (int i = 0; i < changes; ++i) {
            x[rnd.next(0, n - 1)] = char('0' + rnd.next(0, 8));
        }
        if (x[0] == '0') x[0] = char('1' + rnd.next(0, 8));
    } else if (mode == 2) {
        x = string(n, '1');
        int zeros = rnd.next(0, n - 1);
        for (int i = 0; i < zeros; ++i) {
            x[rnd.next(1, n - 1)] = '0';
        }
    } else if (mode == 3) {
        x = string(n, '0');
        x[0] = char('1' + rnd.next(0, 8));
        int nonzero = rnd.next(1, min(n, 8));
        for (int i = 0; i < nonzero; ++i) {
            x[rnd.next(0, n - 1)] = char('1' + rnd.next(0, 8));
        }
    } else if (mode == 4) {
        x = string(n, '0');
        x[0] = char('1' + rnd.next(0, 8));
        x[n - 1] = char('1' + rnd.next(0, 8));
    } else if (mode == 5) {
        x = string(n, '0');
        int targetMod = rnd.next(0, 2);
        int sumMod = 0;
        for (int i = 0; i < n - 1; ++i) {
            int digit = (i == 0) ? rnd.next(1, 9) : rnd.next(0, 9);
            x[i] = char('0' + digit);
            sumMod = (sumMod + digit) % 3;
        }
        int last = (targetMod - sumMod + 3) % 3;
        if (rnd.next(0, 1)) last += 3;
        if (rnd.next(0, 1) && last + 3 <= 9) last += 3;
        x[n - 1] = char('0' + last);
    } else {
        x = string(n, '0');
        x[0] = char('1' + rnd.next(0, 8));
        for (int i = 1; i < n; ++i) {
            int digit = rnd.next(0, 9);
            if (rnd.next(0, 4) == 0) {
                string multiples = "0369";
                digit = multiples[rnd.next(0, 3)] - '0';
            }
            x[i] = char('0' + digit);
        }
    }

    println(x);
    return 0;
}

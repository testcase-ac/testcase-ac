#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int kim;
    int lee;

    if (mode == 0) {
        n = rnd.next(2, 40);
        kim = rnd.next(1, n - 1);
        lee = kim + 1;
    } else if (mode == 1) {
        int exponent = rnd.next(1, 16);
        n = 1 << exponent;
        kim = rnd.next(1, n);
        int distance = 1 << rnd.next(0, exponent);
        lee = kim ^ distance;
        if (lee == 0 || lee > n) lee = n;
        if (kim == lee) lee = kim == 1 ? 2 : 1;
    } else if (mode == 2) {
        n = rnd.next(3, 101);
        if (n % 2 == 0) ++n;
        kim = n;
        lee = rnd.next(1, n - 1);
    } else if (mode == 3) {
        n = rnd.next(2, 100000);
        kim = 1;
        lee = n;
    } else if (mode == 4) {
        n = rnd.next(90000, 100000);
        kim = rnd.next(1, n);
        lee = rnd.next(1, n);
        while (lee == kim) lee = rnd.next(1, n);
    } else if (mode == 5) {
        n = rnd.next(2, 300);
        int maxRound = 0;
        while ((1 << (maxRound + 1)) <= n) ++maxRound;
        int round = rnd.next(1, maxRound);
        int block = 1 << round;
        int start = rnd.next(1, max(1, n - block + 1));
        kim = start + rnd.next(0, block / 2 - 1);
        lee = min(n, start + block / 2 + rnd.next(0, block / 2 - 1));
        if (kim == lee) lee = kim == n ? kim - 1 : kim + 1;
    } else {
        n = rnd.next(2, 1000);
        kim = rnd.next(1, n);
        lee = rnd.next(1, n);
        while (lee == kim) lee = rnd.next(1, n);
    }

    if (rnd.next(0, 1)) swap(kim, lee);
    println(n, kim, lee);

    return 0;
}

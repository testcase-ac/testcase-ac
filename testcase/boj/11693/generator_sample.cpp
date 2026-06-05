#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 0;

    if (mode == 0) {
        n = rnd.next(1, 20);
        m = rnd.any(vector<int>{0, 1, 2, 3, rnd.next(4, 30)});
    } else if (mode == 1) {
        n = rnd.any(smallPrimes);
        if (rnd.next(0, 3) == 0) n = rnd.next(999999900, 1000000000);
        m = rnd.next(1, 1000000000);
    } else if (mode == 2) {
        int base = rnd.any(smallPrimes);
        long long value = 1;
        while (value * base <= 1000000000LL && rnd.next(0, 2) != 0) {
            value *= base;
        }
        if (value == 1) value = base;
        n = (int)value;
        m = rnd.next(0, 1000000);
    } else if (mode == 3) {
        shuffle(smallPrimes.begin(), smallPrimes.end());
        long long value = 1;
        int factors = rnd.next(2, 5);
        for (int i = 0; i < factors; ++i) {
            int repeats = rnd.next(1, 3);
            while (repeats-- > 0 && value * smallPrimes[i] <= 1000000000LL) {
                value *= smallPrimes[i];
            }
        }
        n = (int)value;
        m = rnd.next(1, 100000);
    } else if (mode == 4) {
        int a = rnd.next(25000, 32000);
        int b = rnd.next(25000, 32000);
        n = a * b;
        m = rnd.next(0, 1000000000);
    } else {
        n = rnd.next(1, 1000000000);
        m = rnd.next(0, 1000000000);
    }

    println(n, m);
    return 0;
}

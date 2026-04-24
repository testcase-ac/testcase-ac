#include "testlib.h"
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int cat = rnd.next(0, 5);
    int a = 0, b = 1;
    if (cat == 0) {
        // trivial average = 1
        a = 1; b = 1;
    } else if (cat == 1) {
        // simplest fractional possible = 1/2
        a = 1; b = 2;
    } else if (cat == 2) {
        // impossible small 1/b for b>=3
        b = rnd.next(3, 20);
        a = 1;
    } else if (cat == 3) {
        // integer or >1, then simplify
        int b0 = rnd.next(1, 20);
        int delta = rnd.next(1, 10);
        int a0 = b0 + delta;
        int g = gcd(a0, b0);
        a = a0 / g;
        b = b0 / g;
    } else if (cat == 4) {
        // proper fraction < 1, excluding 1/b cases
        do {
            b = rnd.next(3, 50);
            a = rnd.next(2, b - 1);
        } while (gcd(a, b) != 1);
    } else {
        // general random coprime
        do {
            a = rnd.next(1, 1000);
            b = rnd.next(1, 1000);
        } while (gcd(a, b) != 1);
    }
    printf("%d/%d\n", a, b);
    return 0;
}

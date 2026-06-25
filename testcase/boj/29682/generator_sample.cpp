#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> smallPrimes = {2, 3, 5, 7, 11, 17, 23, 31, 97};
    vector<int> mediumPrimes = {101, 257, 1009, 10007, 99991, 1000003};
    vector<int> largePrimes = {1000000007, 1000000009, 1999999973};

    int bucket = rnd.next(0, 99);
    int m;
    if (bucket < 35) {
        m = rnd.any(smallPrimes);
    } else if (bucket < 75) {
        m = rnd.any(mediumPrimes);
    } else {
        m = rnd.any(largePrimes);
    }

    int mode = rnd.next(0, 5);
    int a;
    if (mode == 0) {
        a = 1;
    } else if (mode == 1) {
        a = m - 1;
    } else if (mode == 2) {
        a = rnd.next(1, min(m - 1, 20));
    } else if (mode == 3) {
        a = max(1, m - rnd.next(1, min(m - 1, 20)));
    } else if (mode == 4 && m > 3) {
        int center = m / 2;
        int delta = rnd.next(-min(center - 1, 10), min(m - 1 - center, 10));
        a = center + delta;
    } else {
        a = rnd.next(1, m - 1);
    }

    println(a, m);
    return 0;
}

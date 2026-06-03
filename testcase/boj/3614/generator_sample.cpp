#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 999999;
    int mode = rnd.next(0, 7);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 30);
    } else if (mode == 1) {
        n = rnd.next(31, 1000);
    } else if (mode == 2) {
        n = maxN - rnd.next(0, 1000);
    } else if (mode == 3) {
        vector<int> primes = {
            2, 3, 5, 7, 11, 13, 17, 19, 29, 31, 37, 41, 97, 101, 997, 1009,
            10007, 99991, 999983
        };
        n = rnd.any(primes);
    } else if (mode == 4) {
        int base = rnd.next(2, 20);
        n = 1;
        while (n <= maxN / base && rnd.next(0, 1)) {
            n *= base;
        }
        if (n == 1) n = base;
    } else if (mode == 5) {
        vector<int> smooth = {360, 720, 840, 1260, 1680, 2520, 5040, 7560,
                              10080, 15120, 27720, 55440, 83160, 166320,
                              332640, 498960, 720720};
        n = rnd.any(smooth);
    } else if (mode == 6) {
        int a = rnd.next(1, 999);
        int b = rnd.next(1, 999);
        n = min(maxN, a * b);
    } else {
        n = rnd.next(1, maxN);
    }

    println(n);
    return 0;
}

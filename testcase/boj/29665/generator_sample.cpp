#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int randomPrime() {
    static const vector<int> smallPrimes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
        53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 127, 257,
        569, 673, 997, 1009, 10007, 99991, 1000003, 999999937
    };
    return rnd.any(smallPrimes);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    static const vector<int> largeN = {99980, 99991, 100000};
    static const vector<int> extremeK = {1, 0};

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 12);
        k = rnd.next(1, n);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        k = rnd.next((n + 2) / 2, n);
    } else if (mode == 2) {
        k = rnd.next(1, 18);
        n = rnd.next(k, min(2 * k + 4, 40));
    } else if (mode == 3) {
        n = rnd.next(20, 120);
        k = rnd.next(1, n);
    } else if (mode == 4) {
        n = rnd.any(largeN);
        k = rnd.next(max(1, n / 2 - 5), min(n, n / 2 + 5));
    } else {
        n = rnd.next(1, 100000);
        k = rnd.any(extremeK);
        if (k == 0) {
            k = n;
        }
    }

    println(n, k, randomPrime());
    return 0;
}

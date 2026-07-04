#include "testlib.h"
#include <cmath>
#include <vector>
using namespace std;

bool isPrime(int x) {
    if (x < 2) return false;
    if (x % 2 == 0) return x == 2;
    int lim = floor(sqrt((double)x));
    for (int d = 3; d <= lim; d += 2) {
        if (x % d == 0) return false;
    }
    return true;
}

int previousPrime(int x) {
    if (x <= 2) return 2;
    if (x % 2 == 0) --x;
    while (!isPrime(x)) x -= 2;
    return x;
}

int randomPrime(int lo, int hi) {
    int candidate = rnd.next(lo, hi);
    return previousPrime(candidate);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxValue = 500000000;
    vector<int> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 101, 131, 719, 727, 9973};
    int mode = rnd.next(0, 7);

    int N;
    int K;
    int P;

    if (mode == 0) {
        N = rnd.next(2, 4);
        K = rnd.next(2, 5);
        P = rnd.any(smallPrimes);
    } else if (mode == 1) {
        N = rnd.next(5, 12);
        K = 2;
        P = rnd.any(smallPrimes);
    } else if (mode == 2) {
        N = rnd.next(10, 13);
        K = rnd.next(2, 4);
        P = randomPrime(100000, maxValue);
    } else if (mode == 3) {
        N = rnd.next(13, 100);
        K = rnd.next(2, 10);
        P = randomPrime(1000000, maxValue);
    } else if (mode == 4) {
        N = rnd.next(2, 12);
        K = rnd.next(100, maxValue);
        P = randomPrime(1000000, maxValue);
    } else if (mode == 5) {
        vector<int> boundaryN = {11, 12, 13};
        N = rnd.any(boundaryN);
        K = rnd.next(2, 3);
        P = randomPrime(400000000, maxValue);
    } else {
        N = rnd.next(2, maxValue);
        K = rnd.next(2, maxValue);
        P = randomPrime(400000000, maxValue);
    }

    println(N, K, P);
    return 0;
}

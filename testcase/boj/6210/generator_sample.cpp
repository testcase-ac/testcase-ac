#include "testlib.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int d = 3; d * d <= n; d += 2) {
        if (n % d == 0) return false;
    }
    return true;
}

vector<int> primesWithDigits(int digits) {
    int lo = 1;
    for (int i = 1; i < digits; ++i) lo *= 10;
    int hi = lo * 10 - 1;
    if (digits == 1) lo = 2;

    vector<int> primes;
    for (int value = lo; value <= hi; ++value) {
        if (isPrime(value)) primes.push_back(value);
    }
    return primes;
}

int concatPrimePair(int digits) {
    vector<int> primes = primesWithDigits(digits);
    int first = rnd.any(primes);
    if (digits == 5) {
        vector<int> smallFirsts;
        for (int prime : primes) {
            if (prime <= 19999) smallFirsts.push_back(prime);
        }
        first = rnd.any(smallFirsts);
    }
    int second = rnd.any(primes);
    return static_cast<int>(stoll(to_string(first) + to_string(second)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int d = rnd.next(1, 5);
    int n;

    if (mode == 0) {
        d = 1;
        n = rnd.next(1, 100);
    } else if (mode == 1) {
        n = rnd.next(1, 5000);
    } else if (mode == 2) {
        int answerLike = concatPrimePair(d);
        int backstep = rnd.next(0, min(answerLike - 1, 50));
        n = answerLike - backstep;
    } else if (mode == 3) {
        vector<int> boundaries = {9, 10, 99, 100, 999, 1000, 9999, 10000,
                                  99999, 100000, 999999, 1000000};
        n = rnd.any(boundaries) + rnd.next(-3, 3);
        n = max(1, n);
    } else if (mode == 4) {
        d = 5;
        n = rnd.next(900000000, 2000000000);
    } else {
        n = rnd.next(1, 2000000000);
    }

    println(d, n);
    return 0;
}

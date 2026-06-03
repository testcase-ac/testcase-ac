#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static bool isPrime(int n) {
    if (n < 2) {
        return false;
    }
    for (int d = 2; d * d <= n; ++d) {
        if (n % d == 0) {
            return false;
        }
    }
    return true;
}

static int readFourDigitPrime(const char* name) {
    int value = inf.readInt(1000, 9999, name);
    ensuref(isPrime(value), "%s must be a four-digit prime, got %d", name, value);
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);
        readFourDigitPrime("A");
        inf.readSpace();
        readFourDigitPrime("B");
        inf.readEoln();
    }

    inf.readEof();
}

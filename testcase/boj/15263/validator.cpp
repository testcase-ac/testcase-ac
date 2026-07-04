#include "testlib.h"

using namespace std;

bool isPrime(int x) {
    if (x < 2) {
        return false;
    }
    if (x % 2 == 0) {
        return x == 2;
    }
    for (int d = 3; 1LL * d * d <= x; d += 2) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(2LL, 1000000000000000000LL, "n");
    inf.readSpace();
    int p = inf.readInt(2, 9999999, "p");
    inf.readSpace();
    int r = inf.readInt(0, p - 1, "r");
    inf.readEoln();

    ensuref(isPrime(p), "p must be prime, got %d", p);

    inf.readEof();
}

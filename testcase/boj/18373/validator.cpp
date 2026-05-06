#include "testlib.h"
#include <cmath>
using namespace std;

bool isPrime(int x) {
    if (x < 2) return false;
    if (x % 2 == 0) return x == 2;
    int lim = floor(sqrt((double)x));
    for (int i = 3; i <= lim; i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, K, P on one line separated by spaces
    long long N = inf.readLong(2, 500000000LL, "N");
    inf.readSpace();
    long long K = inf.readLong(2, 500000000LL, "K");
    inf.readSpace();
    long long P_ll = inf.readLong(2, 500000000LL, "P");
    inf.readEoln();

    // Check P fits in int and is prime
    ensuref(P_ll <= 0x7fffffff,
            "P too large for primality check: %lld", P_ll);
    int P = int(P_ll);
    ensuref(isPrime(P),
            "P is not prime: %d", P);

    inf.readEof();
    return 0;
}

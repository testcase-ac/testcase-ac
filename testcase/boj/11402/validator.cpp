#include "testlib.h"
using namespace std;

bool isPrime(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, K, M on a single line
    long long N = inf.readLong(1LL, 1000000000000000000LL, "N");
    inf.readSpace();
    long long K = inf.readLong(0LL, N, "K");
    inf.readSpace();
    int M = inf.readInt(2, 2000, "M");
    inf.readEoln();

    // Validate that M is prime
    ensuref(isPrime(M), "M must be prime, but %d is not prime", M);

    inf.readEof();
    return 0;
}

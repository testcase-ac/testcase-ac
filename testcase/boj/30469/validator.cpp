#include "testlib.h"

bool isPrime(int x) {
    if (x < 2) return false;
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(11, 97, "A");
    inf.readSpace();
    int b = inf.readInt(11, 97, "B");
    inf.readSpace();
    int n = inf.readInt(7, 100, "N");
    inf.readEoln();

    ensuref(isPrime(a), "A must be prime: %d", a);
    ensuref(isPrime(b), "B must be prime: %d", b);

    inf.readEof();
}

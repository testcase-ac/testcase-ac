#include "testlib.h"
using namespace std;

bool isPrime(int x) {
    if (x < 2) return false;
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(2, 211, "P");
    inf.readEoln();

    ensuref(isPrime(p), "P must be prime: %d", p);

    inf.readEof();
    return 0;
}

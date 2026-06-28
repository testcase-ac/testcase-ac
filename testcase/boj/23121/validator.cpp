#include "testlib.h"

using namespace std;

bool isPrime(int p) {
    if (p < 2) {
        return false;
    }
    for (long long d = 2; d * d <= p; ++d) {
        if (p % d == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(2, 1000000007, "p");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    ensuref(isPrime(p), "p must be prime: %d", p);

    for (int i = 1; i <= q; ++i) {
        setTestCase(i);

        int a = inf.readInt(0, p - 1, "a_i");
        inf.readSpace();
        int b = inf.readInt(0, p - 1, "b_i");
        inf.readSpace();
        inf.readInt(0, p - 1, "c_i");
        inf.readSpace();
        inf.readInt(0, p - 1, "d_i");
        inf.readEoln();

        ensuref(((long long)a + b) % p != 0,
                "a_i + b_i must not be divisible by p at query %d", i);
    }

    inf.readEof();
    return 0;
}

#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXV = 2147483647; // 2^31 - 1

    while (true) {
        long long a = inf.readLong(0LL, MAXV, "a");
        inf.readSpace();
        long long b = inf.readLong(0LL, MAXV, "b");
        inf.readEoln();

        // The last line must be "0 0"
        if (a == 0 && b == 0) {
            break;
        }

        // Both numbers must be positive natural numbers (>=1)
        ensuref(a >= 1 && b >= 1, "Both numbers must be positive natural numbers, got (%lld, %lld)", a, b);
    }

    inf.readEof();
}

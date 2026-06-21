#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long a = inf.readLong(1LL, 1000000000LL, "A");
    inf.readSpace();
    long long b = inf.readLong(1LL, 1000000000LL, "B");
    inf.readSpace();
    long long c = inf.readLong(1LL, 1000000000000000000LL, "C");
    inf.readEoln();

    ensuref(c <= min(a, b) * 1000000000LL,
            "C must be at most min(A, B) * 1000000000, got A=%lld, B=%lld, C=%lld",
            a, b, c);

    inf.readEof();
}

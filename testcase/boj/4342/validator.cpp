#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXV = 2147483647; // 2^31 - 1
    const int MAX_CASES = 100000;

    int cases = 0;
    while (true) {
        long long a = inf.readLong(0LL, MAXV, "a");
        inf.readSpace();
        long long b = inf.readLong(0LL, MAXV, "b");
        inf.readEoln();

        if (a == 0 && b == 0) {
            break;
        }

        ensuref(a >= 1, "a must be a positive natural number or the final sentinel, got %lld", a);
        ensuref(b >= 1, "b must be a positive natural number or the final sentinel, got %lld", b);
        // CHECK: The statement omits a case-count bound; this follows repo validator policy.
        ensuref(++cases <= MAX_CASES, "too many game lines: %d", cases);
    }

    inf.readEof();
}

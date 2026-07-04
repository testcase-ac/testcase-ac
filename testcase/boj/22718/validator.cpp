#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr long long MAX_K = 1000000000000000LL;
    // CHECK: The statement does not bound the number of cases; cap it locally.
    constexpr int MAX_CASES = 100000;

    int cases = 0;
    while (true) {
        long long k = inf.readLong(0LL, MAX_K, "k");
        inf.readEoln();

        if (k == 0) {
            break;
        }

        ++cases;
        ensuref(cases <= MAX_CASES, "too many test cases: %d", cases);
    }

    inf.readEof();
}

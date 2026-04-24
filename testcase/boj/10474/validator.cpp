#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long LIMIT = 2147483647LL;
    int tc = 0;
    while (true) {
        // Read two integers, allowing 0 for sentinel
        long long num = inf.readLong(0LL, LIMIT, "numerator");
        inf.readSpace();
        long long den = inf.readLong(0LL, LIMIT, "denominator");
        inf.readEoln();

        // Check for termination condition
        if (num == 0 && den == 0) {
            break;
        }

        // This is a real test case
        ++tc;
        ensuref(num >= 1,
                "In test case %d, numerator must be at least 1 but found %lld",
                tc, num);
        ensuref(den >= 1,
                "In test case %d, denominator must be at least 1 but found %lld",
                tc, den);
        // Upper bounds are enforced by readLong
    }

    // No more test cases; check count constraint (implicit max 1e5)
    ensuref(tc <= 100000,
            "Number of test cases must not exceed 100000 but found %d",
            tc);

    inf.readEof();
    return 0;
}

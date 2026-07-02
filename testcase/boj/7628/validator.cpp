#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCases = 0;
    while (true) {
        long long n = inf.readLong(0LL, 1000000000000LL, "N");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++testCases;
        // CHECK: The statement does not bound the number of query lines.
        ensuref(testCases <= 100000, "too many test cases: %d", testCases);
    }

    inf.readEof();
}

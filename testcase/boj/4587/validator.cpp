#include "testlib.h"

#include <numeric>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        int m = inf.readInt(0, 99, "M");
        inf.readSpace();
        int n = inf.readInt(0, 99, "N");
        inf.readEoln();

        if (m == 0 && n == 0) {
            break;
        }

        ++caseCount;
        // CHECK: the statement gives no testcase-count limit; use the repo default cap.
        ensuref(caseCount <= 100000, "too many test cases: %d", caseCount);
        ensuref(1 < m, "M must be greater than 1, got %d", m);
        ensuref(m < n, "M must be less than N, got M=%d N=%d", m, n);
        ensuref(n < 100, "N must be less than 100, got %d", n);
        ensuref(std::gcd(m, n) == 1, "M and N must be coprime, got M=%d N=%d", m, n);
    }

    inf.readEof();
}

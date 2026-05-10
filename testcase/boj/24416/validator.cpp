#include "testlib.h"

using namespace std;

long long fib(int n) {
    if (n <= 2) return 1;
    long long a = 1, b = 1;
    for (int i = 3; i <= n; ++i) {
        long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer n with constraints 5 ≤ n ≤ 40
    int n = inf.readInt(5, 40, "n");
    inf.readEoln();

    // Global property from statement: the answer always exists and
    // they effectively compare counts:
    // - 코드1 (code1) executions == Fibonacci(n)
    // - 코드2 (code2) executions == n - 2
    // Both are well-defined for 5 ≤ n ≤ 40, and within 32-bit range.
    // We check this computability (no overflow) as a safety.
    long long code1 = fib(n);
    long long code2 = n - 2;
    ensuref(code1 > 0, "Computed Fibonacci(n) must be positive for n in [5, 40]");
    ensuref(code1 <= 1000000000LL, "Computed Fibonacci(n) too large for n=%d", n);
    ensuref(code2 >= 3, "n-2 must be at least 3 for n in [5, 40]");

    inf.readEof();
}

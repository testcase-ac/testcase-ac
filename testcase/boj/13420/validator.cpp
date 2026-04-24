#include "testlib.h"
#include <climits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T: unspecified, so assume up to 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read A
        long long A = inf.readLong(LLONG_MIN, LLONG_MAX, "A");
        inf.readSpace();

        // Read operator: one of +, -, *, /
        string op = inf.readToken("[+\\-*/]", "op");
        inf.readSpace();

        // Read B
        long long B = inf.readLong(LLONG_MIN, LLONG_MAX, "B");
        inf.readSpace();

        // Read '=' sign
        inf.readToken("=", "equal_sign");
        inf.readSpace();

        // Read C
        long long C = inf.readLong(LLONG_MIN, LLONG_MAX, "C");
        inf.readEoln();

        // Validate division constraints
        if (op == "/") {
            // Division by zero is not allowed
            ensuref(B != 0,
                    "Division by zero at test case %d: %lld / %lld",
                    tc, A, B);
            // Division overflow for LLONG_MIN / -1 is out of 64-bit range
            ensuref(!(A == LLONG_MIN && B == -1),
                    "Division overflow at test case %d: %lld / %lld",
                    tc, A, B);
            // Must divide evenly
            long long rem = A % B;
            ensuref(rem == 0,
                    "Non-integer division at test case %d: %lld / %lld has remainder %lld",
                    tc, A, B, rem);
        }
    }

    inf.readEof();
    return 0;
}

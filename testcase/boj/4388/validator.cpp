#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        // Read first number as a string of digits
        string a = inf.readToken("[0-9]+", "a");
        inf.readSpace();
        // Read second number
        string b = inf.readToken("[0-9]+", "b");
        inf.readEoln();

        // Each number must have length 1 to 10
        ensuref(a.size() >= 1 && a.size() <= 10,
                "Length of a (%s) must be between 1 and 10", a.c_str());
        ensuref(b.size() >= 1 && b.size() <= 10,
                "Length of b (%s) must be between 1 and 10", b.c_str());

        // No leading zeros unless the number is exactly "0"
        if (a.size() > 1) {
            ensuref(a[0] != '0',
                    "Leading zero detected in a: %s", a.c_str());
        }
        if (b.size() > 1) {
            ensuref(b[0] != '0',
                    "Leading zero detected in b: %s", b.c_str());
        }

        // Check for termination condition
        if (a == "0" && b == "0") {
            break;
        }

        // Count this as a real test case
        cases++;
        // Limit on number of test cases (unspecified in statement => assume ≤ 100k)
        ensuref(cases <= 100000,
                "Too many test cases: %d (maximum is 100000)", cases);
    }

    inf.readEof();
    return 0;
}

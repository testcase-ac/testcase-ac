#include "testlib.h"

#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const double MAX_VALUE = 1e9;  // CHECK: The statement gives no numeric upper bounds; use a practical finite cap.
    const int MAX_TEST_CASES = 100000;  // CHECK: The statement gives no test-case count limit; use the local default cap.

    int testCaseCount = 0;
    while (!inf.eof()) {
        ++testCaseCount;
        setTestCase(testCaseCount);
        ensuref(testCaseCount <= MAX_TEST_CASES, "too many test cases: %d", testCaseCount);

        double r = inf.readDouble(0.0, MAX_VALUE, "r");
        inf.readSpace();
        double h = inf.readDouble(0.0, MAX_VALUE, "h");
        inf.readSpace();
        double d1 = inf.readDouble(0.0, MAX_VALUE, "d_1");
        inf.readSpace();
        double a1 = inf.readDouble(0.0, 360.0, "A_1");
        inf.readSpace();
        double d2 = inf.readDouble(0.0, MAX_VALUE, "d_2");
        inf.readSpace();
        double a2 = inf.readDouble(0.0, 360.0, "A_2");
        inf.readEoln();

        ensuref(r > 0.0, "r must be positive");
        ensuref(h > 0.0, "h must be positive");
        // CHECK: At d = 0 the point is the cone tip, where the angle A is not well-defined.
        ensuref(d1 > 0.0, "d_1 must be positive");
        ensuref(d2 > 0.0, "d_2 must be positive");
        ensuref(a1 < 360.0, "A_1 must be less than 360");
        ensuref(a2 < 360.0, "A_2 must be less than 360");

        double slantHeight = hypot(r, h);
        ensuref(d1 <= slantHeight, "d_1 must not exceed the cone slant height");
        ensuref(d2 <= slantHeight, "d_2 must not exceed the cone slant height");
    }

    ensuref(testCaseCount > 0, "input must contain at least one test case");
    inf.readEof();
}

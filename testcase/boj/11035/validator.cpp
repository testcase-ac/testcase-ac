#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives EOF-terminated test cases but no test-count cap.
    // Use the local default cap for unstated multi-case input.
    constexpr int MAX_TESTS = 100000;

    int tests = 0;
    while (!inf.seekEof()) {
        ++tests;
        ensuref(tests <= MAX_TESTS, "too many test cases: %d", tests);
        setTestCase(tests);

        int n = inf.readInt(3, 1000, "N");
        inf.readSpace();
        int k = inf.readInt(2, n - 1, "K");
        inf.readEoln();
    }

    ensuref(tests > 0, "input must contain at least one test case");
    inf.readEof();
}

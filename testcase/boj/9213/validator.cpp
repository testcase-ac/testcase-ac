#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound the number of tests; use the repo
    // default practical cap.
    constexpr int kMaxTests = 100000;

    int tests = 0;
    while (true) {
        int start = inf.readInt(0, 999999, "start");
        inf.readSpace();
        int stop = inf.readInt(0, 999999, "stop");
        inf.readSpace();
        int badness = inf.readInt(0, 999, "badness");
        inf.readEoln();

        if (start == 0 && stop == 0 && badness == 0) {
            break;
        }

        ++tests;
        ensuref(tests <= kMaxTests, "too many test cases: %d", tests);
        ensuref(2 <= start, "start must be at least 2, got %d", start);
        ensuref(start <= stop, "start must not exceed stop: %d > %d", start, stop);
    }

    inf.readEof();
}

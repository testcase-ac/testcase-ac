#include "testlib.h"

namespace {

constexpr int MAX_TEST_CASES = 100000;
constexpr int MAX_N = 5000;
constexpr int MAX_VALUE = 10000;
constexpr int MAX_TOTAL_STICKS = 2400000;

void readOneOrMoreSpaces() {
    inf.readSpace();
    while (true) {
        char c = inf.readChar();
        if (c != ' ') {
            inf.unreadChar(c);
            break;
        }
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: T is unbounded in the statement; use the local default for absent test-count bounds.
    int tests = inf.readInt(1, MAX_TEST_CASES, "T");
    inf.readEoln();

    int totalSticks = 0;
    for (int tc = 1; tc <= tests; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, MAX_N, "n");
        inf.readEoln();

        totalSticks += n;
        // CHECK: The statement gives no aggregate cap; keep numeric inputs below about 5M scalar tokens.
        ensuref(totalSticks <= MAX_TOTAL_STICKS,
                "total number of sticks exceeds practical cap: %d",
                totalSticks);

        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                readOneOrMoreSpaces();
            }
            inf.readInt(1, MAX_VALUE, "l_i");
            readOneOrMoreSpaces();
            inf.readInt(1, MAX_VALUE, "w_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}

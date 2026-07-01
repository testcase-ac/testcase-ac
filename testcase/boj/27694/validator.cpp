#include "testlib.h"

#include <string>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int maxN = 100000;
    // CHECK: The statement does not give an upper bound for t; this local cap
    // keeps the number of test cases practical while allowing broad coverage.
    constexpr int maxT = 100000;

    int t = inf.readInt(1, maxT, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        std::string blank = inf.readLine("[^]*", "blank_line");
        ensuref(blank.empty(), "test case %d must be preceded by a blank line", tc);

        inf.readInt(1, maxN, "n");
        inf.readEoln();
    }

    inf.readEof();
}

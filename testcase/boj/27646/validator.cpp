#include "testlib.h"

#include <string>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        std::string blank = inf.readLine("[^]*", "blank_line");
        ensuref(blank.empty(), "test case %d must be preceded by a blank line", tc);

        inf.readInt(1, 1000, "n");
        inf.readEoln();
    }

    inf.readEof();
}

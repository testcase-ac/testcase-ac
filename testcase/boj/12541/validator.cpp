#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement only gives N <= 10; require at least one test case.
    int n = inf.readInt(1, 10, "N");
    inf.readEoln();

    for (int tc = 1; tc <= n; ++tc) {
        setTestCase(tc);

        int length = inf.readInt(1, 50, "L");
        inf.readSpace();
        int width = inf.readInt(1, 50, "W");
        inf.readEoln();

        int obstacles = 0;
        for (int row = 1; row <= width; ++row) {
            string line = inf.readToken("[GRWST]+", "row");
            inf.readEoln();

            ensuref(static_cast<int>(line.size()) == length,
                    "row %d has length %d, expected %d",
                    row,
                    static_cast<int>(line.size()),
                    length);

            for (char cell : line) {
                if (cell == 'R' || cell == 'W' || cell == 'T') {
                    ++obstacles;
                }
            }
        }

        ensuref(obstacles < 5,
                "test case has %d obstacles, expected fewer than 5",
                obstacles);
    }

    inf.readEof();
}

#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = inf.readInt(1, 30, "N");
    inf.readEoln();

    for (int tc = 1; tc <= cases; ++tc) {
        setTestCase(tc);

        int length = inf.readInt(1, 50, "L");
        inf.readSpace();
        int width = inf.readInt(1, 50, "W");
        inf.readEoln();

        int obstacles = 0;
        for (int row = 1; row <= width; ++row) {
            string land = inf.readToken("[GRWST]{1,50}", "land_row");
            inf.readEoln();

            ensuref((int)land.size() == length,
                    "case %d row %d has length %d, expected %d",
                    tc,
                    row,
                    (int)land.size(),
                    length);
            for (char cell : land) {
                if (cell == 'R' || cell == 'W' || cell == 'T') {
                    ++obstacles;
                }
            }
        }

        ensuref(obstacles < 20, "case %d has %d obstacles, expected fewer than 20", tc, obstacles);
    }

    inf.readEof();
}

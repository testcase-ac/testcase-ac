#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(200, 200, "N");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int R = inf.readInt(1, 8, "R");
        inf.readSpace();
        int C = inf.readInt(1, 8, "C");
        inf.readEoln();

        int starts = 0;
        int cakes = 0;
        for (int r = 0; r < R; ++r) {
            string row = inf.readToken("[.#OX]{1,8}", "row");
            inf.readEoln();

            ensuref((int)row.size() == C,
                    "row %d has length %d, expected %d",
                    r + 1, (int)row.size(), C);

            for (char cell : row) {
                if (cell == 'O') {
                    ++starts;
                } else if (cell == 'X') {
                    ++cakes;
                }
            }
        }

        ensuref(starts == 1, "case has %d starting positions, expected 1", starts);
        ensuref(cakes == 1, "case has %d cake positions, expected 1", cakes);
    }

    inf.readEof();
    return 0;
}

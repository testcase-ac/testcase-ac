#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 200, "R");
    inf.readSpace();
    int c = inf.readInt(1, 200, "C");
    inf.readSpace();
    int n = inf.readInt(3, 200, "N");
    inf.readEoln();

    int cells = r * c;
    ensuref(3 <= cells && cells <= 200, "R*C must be in [3, 200], found %d", cells);
    ensuref(n <= cells, "N must not exceed R*C: N=%d, R*C=%d", n, cells);

    int a1 = inf.readInt(1, n, "a_1");
    inf.readSpace();
    int a2 = inf.readInt(1, n, "a_2");
    inf.readSpace();
    int a3 = inf.readInt(1, n, "a_3");
    inf.readEoln();

    set<int> special = {a1, a2, a3};
    ensuref(special.size() == 3, "a_1, a_2, and a_3 must be distinct");

    inf.readInt(1, 10000, "bonus_12");
    inf.readSpace();
    inf.readInt(1, 10000, "bonus_23");
    inf.readSpace();
    inf.readInt(1, 10000, "bonus_13");
    inf.readEoln();

    for (int row = 1; row <= r; ++row) {
        for (int col = 1; col <= c; ++col) {
            if (col > 1) {
                inf.readSpace();
            }
            inf.readInt(1, 10000, "stage_value");
        }
        inf.readEoln();
    }

    inf.readEof();
}

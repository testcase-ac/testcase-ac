#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    int previousA = 0;
    int previousB = 0;
    for (int column = 1; column <= m; ++column) {
        int a = inf.readInt(0, n, "A");
        inf.readSpace();
        int b = inf.readInt(0, n, "B");
        inf.readEoln();

        ensuref((a == 0 && b == 0) || (1 <= a && a <= b),
                "column %d must be empty (0 0) or satisfy 1 <= A <= B", column);

        if (a != 0 && previousA != 0) {
            bool overlap = max(a, previousA) <= min(b, previousB);
            ensuref(!overlap || (b == n) == (previousB == n),
                    "columns %d and %d connect a floating block to a floor block",
                    column - 1, column);
            ensuref(b + 1 != previousA && previousB + 1 != a,
                    "columns %d and %d touch only at a corner", column - 1, column);
        }

        previousA = a;
        previousB = b;
    }

    inf.readEof();
}

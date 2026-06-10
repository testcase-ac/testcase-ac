#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 9, "n");
    inf.readSpace();
    int m = inf.readInt(0, n, "m");
    inf.readEoln();

    inf.readInt(1, 10, "x");
    inf.readSpace();
    inf.readInt(1, 10, "y");
    inf.readEoln();

    set<int> positions;
    set<int> digits;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(0, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, 9, "b");
        inf.readEoln();

        if (a != 0) {
            ensuref(positions.insert(a).second,
                    "position %d is repeated at info index %d", a, i + 1);
        }
        ensuref(digits.insert(b).second,
                "digit %d is repeated at info index %d", b, i + 1);
    }

    inf.readEof();
}

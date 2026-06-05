#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int l = inf.readInt(5, 1000, "L");
    inf.readSpace();
    int n = inf.readInt(2, 100, "N");
    inf.readSpace();
    inf.readInt(1, 1000, "T");
    inf.readEoln();

    set<int> positions;
    int parity = -1;
    for (int i = 0; i < n; ++i) {
        int s = inf.readInt(1, l - 1, "S_i");
        inf.readSpace();
        inf.readToken("L|R", "C_i");
        inf.readEoln();

        ensuref(positions.insert(s).second,
                "duplicate starting position at ball %d: %d", i + 1, s);
        if (parity == -1) {
            parity = s % 2;
        } else {
            ensuref(s % 2 == parity,
                    "starting positions at ball %d do not all have even pairwise distances", i + 1);
        }
    }

    inf.readEof();
}

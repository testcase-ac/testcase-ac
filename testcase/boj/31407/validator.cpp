#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 70, "N");
    inf.readSpace();
    int l = inf.readInt(1, 100, "L");
    inf.readEoln();

    set<int> positions;
    for (int i = 1; i <= n; ++i) {
        int p = inf.readInt(0, l - 1, "P_i");
        inf.readSpace();
        string c = inf.readToken("L|R", "C_i");
        inf.readEoln();

        ensuref(positions.insert(p).second,
                "duplicate initial position at mushroom %d: P_i=%d", i, p);
    }

    inf.readEof();
}

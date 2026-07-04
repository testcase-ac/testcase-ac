#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "n");
    inf.readEoln();

    int t = inf.readInt(0, 25000000, "t");
    inf.readEoln();

    for (int i = 0; i < t; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readSpace();
        int c = inf.readInt(0, 10000, "c");
        inf.readEoln();

        ensuref(x != y, "route %d connects city %d to itself", i + 1, x);
    }

    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    set<int> storeCities;
    for (int i = 0; i < k; ++i) {
        int z = inf.readInt(1, n, "z");
        inf.readSpace();
        int p = inf.readInt(0, 10000, "p");
        inf.readEoln();

        ensuref(storeCities.insert(z).second,
                "store city %d appears more than once", z);
    }

    inf.readInt(1, n, "d");
    inf.readEoln();
    inf.readEof();
}

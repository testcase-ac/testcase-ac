#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    set<int> seen;
    for (int i = 1; i <= n; ++i) {
        int grumpiness = inf.readInt(1, 100000, "grumpiness");
        inf.readEoln();

        ensuref(seen.insert(grumpiness).second,
                "duplicate grumpiness at cow %d: %d", i, grumpiness);
    }

    inf.readEof();
}

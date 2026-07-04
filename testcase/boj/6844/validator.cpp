#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const set<int> fixedMotels = {
        0, 990, 1010, 1970, 2030, 2940, 3060,
        3930, 4060, 4970, 5030, 5990, 6010, 7000,
    };

    int a = inf.readInt(1, 7000, "A");
    inf.readEoln();
    inf.readInt(a, 7000, "B");
    inf.readEoln();

    int n = inf.readInt(0, 20, "N");
    inf.readEoln();

    set<int> motels = fixedMotels;
    for (int i = 0; i < n; ++i) {
        int m = inf.readInt(1, 6999, "m");
        inf.readEoln();
        ensuref(motels.insert(m).second,
                "duplicate motel location at added motel index %d: %d",
                i + 1, m);
    }

    inf.readEof();
}

#include "testlib.h"

#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "N");
    inf.readEoln();

    unordered_set<int> seenHappiness;
    unordered_set<int> seenFatigue;
    seenHappiness.reserve(n * 2);
    seenFatigue.reserve(n * 2);

    for (int i = 1; i <= n; ++i) {
        int u = inf.readInt(0, 1000000000, "u_i");
        inf.readSpace();
        int v = inf.readInt(0, 1000000000, "v_i");
        inf.readEoln();

        if (u != 0) {
            ensuref(seenHappiness.insert(u).second,
                    "nonzero happiness value is duplicated at year %d: %d", i, u);
        }
        if (v != 0) {
            ensuref(seenFatigue.insert(v).second,
                    "nonzero fatigue value is duplicated at year %d: %d", i, v);
        }
    }

    inf.readEof();
}

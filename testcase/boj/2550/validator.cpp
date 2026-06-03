#include "testlib.h"

#include <vector>

using namespace std;

static void ensurePermutation(const vector<int>& values, int n, const char* name) {
    vector<bool> seen(n + 1, false);
    for (int i = 0; i < n; ++i) {
        int value = values[i];
        ensuref(!seen[value], "%s is not a permutation: duplicate value %d at index %d",
                name, value, i + 1);
        seen[value] = true;
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    vector<int> switches = inf.readInts(n, 1, n, "switch_i");
    inf.readEoln();
    ensurePermutation(switches, n, "switches");

    vector<int> bulbs = inf.readInts(n, 1, n, "bulb_i");
    inf.readEoln();
    ensurePermutation(bulbs, n, "bulbs");

    inf.readEof();
}

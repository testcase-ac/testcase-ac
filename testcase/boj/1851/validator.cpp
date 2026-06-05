#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    set<int> weights;
    for (int i = 0; i < n; ++i) {
        int weight = inf.readInt(1, 1000000, "weight");
        inf.readEoln();

        ensuref(weights.insert(weight).second,
                "duplicate weight at index %d: %d", i + 1, weight);
    }

    inf.readEof();
    return 0;
}

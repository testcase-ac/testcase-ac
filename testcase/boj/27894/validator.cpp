#include "testlib.h"

#include <vector>

using namespace std;

vector<int> readPermutation(int n, const char* name) {
    vector<int> values(n);
    vector<int> seen(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        values[i] = inf.readInt(1, n, name);
        ensuref(!seen[values[i]], "%s is not a permutation: value %d appears more than once", name, values[i]);
        seen[values[i]] = 1;
    }
    inf.readEoln();

    return values;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "N");
    inf.readEoln();

    readPermutation(n, "original_plan");
    readPermutation(n, "ideal_plan");

    inf.readEof();
}

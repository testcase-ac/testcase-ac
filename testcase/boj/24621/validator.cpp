#include "testlib.h"

#include <vector>
using namespace std;

static vector<int> readPermutation(int n, const char* name) {
    vector<int> values = inf.readInts(n, 1, n, name);
    inf.readEoln();

    vector<int> seen(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        ensuref(!seen[values[i]], "%s is not a permutation: duplicate value %d at position %d",
                name, values[i], i + 1);
        seen[values[i]] = 1;
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    readPermutation(n, "a");
    readPermutation(n, "b");

    inf.readEof();
}

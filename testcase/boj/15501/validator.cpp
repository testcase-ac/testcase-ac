#include "testlib.h"

#include <vector>

using namespace std;

static vector<int> readPermutation(int n, const char* name) {
    vector<int> values(n);
    vector<char> seen(n + 1, false);

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }

        values[i] = inf.readInt(1, n, name);
        ensuref(!seen[values[i]], "%s contains duplicate value %d", name, values[i]);
        seen[values[i]] = true;
    }
    inf.readEoln();

    return values;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    readPermutation(n, "initial_sequence");
    readPermutation(n, "target_sequence");

    inf.readEof();
}

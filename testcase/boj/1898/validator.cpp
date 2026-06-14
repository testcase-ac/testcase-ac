#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 50000, "n");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        int value = inf.readInt(1, n, "S_i");
        inf.readEoln();

        ensuref(!seen[value], "S_i is not a permutation: duplicate value %d at index %d", value, i);
        seen[value] = true;
    }

    inf.readEof();
}

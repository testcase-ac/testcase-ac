#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    vector<bool> seen(n + 1);
    for (int i = 1; i <= n; ++i) {
        int value = inf.readInt(1, n, "A_i");
        inf.readEoln();

        ensuref(!seen[value], "A is not a permutation: duplicate cow %d at position %d", value, i);
        seen[value] = true;
    }

    fill(seen.begin(), seen.end(), false);
    for (int i = 1; i <= n; ++i) {
        int value = inf.readInt(1, n, "B_i");
        inf.readEoln();

        ensuref(!seen[value], "B is not a permutation: duplicate cow %d at position %d", value, i);
        seen[value] = true;
    }

    inf.readEof();
}

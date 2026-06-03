#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 250000, "n");
    inf.readEoln();

    vector<bool> seen(n, false);
    for (int i = 0; i < n; ++i) {
        int value = inf.readInt(0, n - 1, "p_i");
        inf.readEoln();

        ensuref(!seen[value], "duplicate P[%d] value: %d", i, value);
        seen[value] = true;
    }

    inf.readEof();
}

#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int value = inf.readInt(1, n, format("P[%d]", i).c_str());
        ensuref(!seen[value], "P is not a permutation: value %d appears more than once", value);
        seen[value] = true;
    }
    inf.readEoln();
    inf.readEof();
}

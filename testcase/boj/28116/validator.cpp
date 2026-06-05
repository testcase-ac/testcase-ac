#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    vector<int> seen(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int value = inf.readInt(1, n, "A_i");
        ensuref(!seen[value], "A_i is not a permutation: value %d appears more than once", value);
        seen[value] = 1;
    }
    inf.readEoln();
    inf.readEof();
}

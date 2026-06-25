#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    int length = 2 * n;
    vector<int> seen(length + 1, 0);
    for (int i = 1; i <= length; ++i) {
        int p = inf.readInt(1, length, "p_i");
        ensuref(!seen[p], "p_i is not a permutation: value %d appears more than once", p);
        seen[p] = 1;

        if (i < length) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}

#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readEoln();

    vector<int> seen(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int value = inf.readInt(1, n, "permutation_i");
        ensuref(!seen[value], "duplicate value in permutation: %d", value);
        seen[value] = 1;
    }
    inf.readEoln();
    inf.readEof();
}

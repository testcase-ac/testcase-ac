#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int a = inf.readInt(1, n, "A_i");
        ensuref(!seen[a], "A is not a permutation: duplicate value %d at position %d", a, i);
        seen[a] = true;
    }
    inf.readEoln();
    inf.readEof();
}

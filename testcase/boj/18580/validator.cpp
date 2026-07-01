#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    vector<int> seen(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int p = inf.readInt(1, n, "p_i");
        ensuref(!seen[p], "p_i values must be distinct, duplicate value %d at index %d", p, i);
        seen[p] = 1;
    }
    inf.readEoln();
    inf.readEof();
}

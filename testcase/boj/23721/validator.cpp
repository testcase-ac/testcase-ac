#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<int> seen(200001, 0);
    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(1, 200000, "A_i");
        ensuref(!seen[a], "A_i values must be distinct, duplicate value %d at index %d", a, i);
        seen[a] = 1;

        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int l = inf.readInt(1, n, "l");
        inf.readSpace();
        int r = inf.readInt(l, n, "r");
        inf.readEoln();
    }

    inf.readEof();
}

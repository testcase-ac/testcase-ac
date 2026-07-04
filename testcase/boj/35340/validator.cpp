#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 10000, "Q");
    inf.readEoln();

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        a[i] = inf.readInt(1, 1000000000, "a_i");
        if (i > 0) {
            ensuref(a[i - 1] < a[i],
                    "a_i must be strictly increasing at index %d: %d >= %d",
                    i + 1, a[i - 1], a[i]);
        }
    }
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        inf.readInt(1, 1000000000, "x");
        inf.readEoln();
    }

    inf.readEof();
}

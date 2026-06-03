#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        a[i] = inf.readInt(1, 1000, "a_i");
        if (i > 0) {
            ensuref(a[i - 1] < a[i],
                    "numbers must be strictly increasing: a[%d]=%d, a[%d]=%d",
                    i, a[i - 1], i + 1, a[i]);
        }
    }
    inf.readEoln();

    ensuref(a[0] == 1, "the list of usable numbers must include 1");

    inf.readInt(1, 50, "k");
    inf.readEoln();
    inf.readEof();
}

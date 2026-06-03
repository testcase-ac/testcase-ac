#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement says N >= 1, but M >= 1 and 3 <= S < E <= N + 2
    // make N = 1 impossible for any complete input.
    int n = inf.readInt(2, 5000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readSpace();
    int q = inf.readInt(1, n, "Q");
    inf.readSpace();
    int m = inf.readInt(1, 50000, "M");
    inf.readEoln();

    set<int> sleeping;
    for (int i = 0; i < k; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int student = inf.readInt(3, n + 2, "sleeping_i");
        ensuref(sleeping.insert(student).second,
                "duplicate sleeping student at index %d: %d", i + 1, student);
    }
    inf.readEoln();

    set<int> receivers;
    for (int i = 0; i < q; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int student = inf.readInt(3, n + 2, "receiver_i");
        ensuref(receivers.insert(student).second,
                "duplicate code receiver at index %d: %d", i + 1, student);
    }
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        int s = inf.readInt(3, n + 1, "S");
        inf.readSpace();
        int e = inf.readInt(s + 1, n + 2, "E");
        inf.readEoln();
    }

    inf.readEof();
}

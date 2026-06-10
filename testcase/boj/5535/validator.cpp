#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int d = inf.readInt(2, 200, "D");
    inf.readSpace();
    // CHECK: BOJ Korean statement gives 2 <= N <= 200; the original Japanese
    // variant gives 1 <= N <= 200.
    int n = inf.readInt(2, 200, "N");
    inf.readEoln();

    vector<int> temperatures(d);
    for (int i = 0; i < d; ++i) {
        temperatures[i] = inf.readInt(0, 60, "T_i");
        inf.readEoln();
    }

    vector<int> a(n), b(n), c(n);
    for (int j = 0; j < n; ++j) {
        a[j] = inf.readInt(0, 60, "A_j");
        inf.readSpace();
        b[j] = inf.readInt(a[j], 60, "B_j");
        inf.readSpace();
        c[j] = inf.readInt(0, 100, "C_j");
        inf.readEoln();
    }

    for (int i = 0; i < d; ++i) {
        bool hasWearable = false;
        for (int j = 0; j < n; ++j) {
            if (a[j] <= temperatures[i] && temperatures[i] <= b[j]) {
                hasWearable = true;
                break;
            }
        }
        ensuref(hasWearable, "day %d has no wearable clothing for temperature %d",
                i + 1, temperatures[i]);
    }

    inf.readEof();
}

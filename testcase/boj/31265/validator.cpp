#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    inf.readInt(1, 10000, "M");
    inf.readEoln();

    vector<int> d(n);
    int total_d = 0;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        d[i] = inf.readInt(1, 1000, "d_i");
        total_d += d[i];
    }
    ensuref(total_d <= 1000, "sum of d_i must be at most 1000, got %d", total_d);
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d[i]; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 1000, "t_ij");
        }
        inf.readEoln();
    }

    inf.readEof();
}

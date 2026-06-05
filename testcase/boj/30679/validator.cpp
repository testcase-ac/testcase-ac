#include "testlib.h"

#include <algorithm>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100, "M");
    inf.readEoln();

    int maxValue = std::min(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            inf.readInt(1, maxValue, "A_i_j");
            if (j + 1 == m) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}

#include "testlib.h"

#include <vector>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 3000, "N");
    inf.readEoln();
    ensuref(n % 2 == 0, "N must be even: %d", n);

    int center_lo = n / 2 - 1;
    int center_hi = n / 2;
    for (int i = 0; i < n; ++i) {
        std::vector<int> row = inf.readInts(n, -25, 25, "a_i_j");
        inf.readEoln();

        for (int j = 0; j < n; ++j) {
            bool is_center = center_lo <= i && i <= center_hi &&
                             center_lo <= j && j <= center_hi;
            ensuref(!is_center || row[j] == 0,
                    "central 2x2 cell (%d, %d) must be 0, found %d",
                    i + 1, j + 1, row[j]);
        }
    }

    inf.readEof();
}

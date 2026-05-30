#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "N");
    inf.readEoln();

    int gems = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int cell = inf.readInt(0, 2, "cell");
            if (cell == 2) {
                ++gems;
            }
        }
        inf.readEoln();
    }

    // CHECK: The opening description implies impurities and gems exist, but the
    // formal Input section only caps gems, so do not require minimum counts.
    ensuref(gems <= 15, "number of gems must be at most 15, got %d", gems);
    inf.readEof();
}

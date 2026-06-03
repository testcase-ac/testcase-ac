#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }

            int weight = inf.readInt(0, 150000, "w");
            if (i == j) {
                ensuref(weight == 0,
                        "self-loop weight at row %d column %d must be 0, got %d",
                        i + 1,
                        j + 1,
                        weight);
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}

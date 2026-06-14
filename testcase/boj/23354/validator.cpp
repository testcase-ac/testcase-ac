#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 1000, "N");
    inf.readEoln();

    int base_count = 0;
    int deserter_count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int value = inf.readInt(-1, 1000, "cell");
            ensuref(value == -1 || value == 0 || value >= 1,
                    "invalid cell value at row %d column %d: %d", i + 1, j + 1, value);

            if (value == -1) {
                ++base_count;
            } else if (value == 0) {
                ++deserter_count;
            }

            if (j + 1 < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    ensuref(base_count == 1, "expected exactly one base, found %d", base_count);
    ensuref(deserter_count <= 5, "expected at most five deserters, found %d", deserter_count);

    inf.readEof();
}

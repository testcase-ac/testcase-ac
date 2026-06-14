#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    int legion_count = 0;
    int shinei_count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }

            int cell = inf.readInt(0, 2, "cell");
            if (cell == 1) {
                ++legion_count;
            } else if (cell == 2) {
                ++shinei_count;
            }
        }
        inf.readEoln();
    }

    ensuref(legion_count <= 10, "number of Legions must be at most 10, got %d", legion_count);
    ensuref(legion_count <= n * n - 1,
            "number of Legions must be at most N^2 - 1, got %d for N=%d",
            legion_count, n);
    ensuref(shinei_count == 1, "Shinei's position must be unique, got %d", shinei_count);

    inf.readEof();
}

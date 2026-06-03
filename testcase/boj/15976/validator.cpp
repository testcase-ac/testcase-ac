#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxCount = 300000;
    const int maxIndex = 1000000000 - 1;
    const int maxValue = 3000;
    const int maxShift = 1000000000;

    int n = inf.readInt(1, maxCount, "N");
    inf.readEoln();

    int prevIndex = -1;
    for (int i = 0; i < n; ++i) {
        int index = inf.readInt(0, maxIndex, "x_index");
        inf.readSpace();
        inf.readInt(1, maxValue, "x_value");
        inf.readEoln();

        ensuref(index > prevIndex,
                "X indices must be strictly increasing: previous=%d current=%d at row %d",
                prevIndex, index, i + 1);
        prevIndex = index;
    }

    int m = inf.readInt(1, maxCount, "M");
    inf.readEoln();

    prevIndex = -1;
    for (int i = 0; i < m; ++i) {
        int index = inf.readInt(0, maxIndex, "y_index");
        inf.readSpace();
        inf.readInt(1, maxValue, "y_value");
        inf.readEoln();

        ensuref(index > prevIndex,
                "Y indices must be strictly increasing: previous=%d current=%d at row %d",
                prevIndex, index, i + 1);
        prevIndex = index;
    }

    int a = inf.readInt(-maxShift, maxShift, "a");
    inf.readEoln();
    int b = inf.readInt(a, maxShift, "b");
    inf.readEoln();

    inf.readEof();
}

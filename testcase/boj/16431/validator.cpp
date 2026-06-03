#include "testlib.h"
using namespace std;

struct Point {
    int r;
    int c;
};

Point readPoint(const char* rowName, const char* colName) {
    Point p;
    p.r = inf.readInt(1, 1000, rowName);
    inf.readSpace();
    p.c = inf.readInt(1, 1000, colName);
    inf.readEoln();
    return p;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    Point bessie = readPoint("B_r", "B_c");
    Point daisy = readPoint("D_r", "D_c");
    Point john = readPoint("J_r", "J_c");

    ensuref(john.r != bessie.r || john.c != bessie.c,
            "John starts on Bessie's cell: (%d, %d)", john.r, john.c);
    ensuref(john.r != daisy.r || john.c != daisy.c,
            "John starts on Daisy's cell: (%d, %d)", john.r, john.c);

    inf.readEof();
    return 0;
}

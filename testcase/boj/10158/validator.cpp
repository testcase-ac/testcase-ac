#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: w and h
    int w = inf.readInt(2, 40000, "w");
    inf.readSpace();
    int h = inf.readInt(2, 40000, "h");
    inf.readEoln();

    // Second line: p and q
    // 0 < p < w, 0 < q < h
    int p = inf.readInt(1, w - 1, "p");
    inf.readSpace();
    int q = inf.readInt(1, h - 1, "q");
    inf.readEoln();

    // Third line: t
    // 1 <= t <= 200,000,000
    inf.readInt(1, 200000000, "t");
    inf.readEoln();

    inf.readEof();
    return 0;
}

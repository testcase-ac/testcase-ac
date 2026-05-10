#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, d, e, x, y
    int N = inf.readInt(2, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(2, 10000, "M");
    inf.readSpace();
    int d = inf.readInt(1, 10000, "d");
    inf.readSpace();
    int e = inf.readInt(1, 10000, "e");
    inf.readSpace();
    int x = inf.readInt(-10000, 10000, "x");
    inf.readSpace();
    int y = inf.readInt(-10000, 10000, "y");
    inf.readEoln();

    inf.readEof();
}

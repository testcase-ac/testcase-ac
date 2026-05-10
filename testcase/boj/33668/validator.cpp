#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int A = inf.readInt(0, 3290, "A");
    inf.readSpace();
    int B = inf.readInt(1, 1000, "B");
    inf.readSpace();
    int C = inf.readInt(1, 1000, "C");
    inf.readSpace();
    int D = inf.readInt(0, C-1, "D"); // 0 <= D < C
    inf.readSpace();
    int E = inf.readInt(0, 200, "E");
    inf.readSpace();
    int F = inf.readInt(0, 100, "F");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        int L = inf.readInt(0, 1000, "L");
        inf.readSpace();
        int H = inf.readInt(1, 1000, "H");
        inf.readSpace();
        int M = inf.readInt(1, 1000, "M");
        inf.readEoln();
    }

    inf.readEof();
}

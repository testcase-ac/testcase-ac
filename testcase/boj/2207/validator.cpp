#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read N and M
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // Each student provides two guesses x and y
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(-M, M, "x_i");
        ensuref(x != 0, "Student %d: x must be non-zero (1 <= |x| <= M), found 0", i+1);
        inf.readSpace();
        int y = inf.readInt(-M, M, "y_i");
        ensuref(y != 0, "Student %d: y must be non-zero (1 <= |y| <= M), found 0", i+1);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

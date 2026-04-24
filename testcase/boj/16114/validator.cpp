#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read X: initial value of x, -100 <= X <= 100
    int X = inf.readInt(-100, 100, "X");
    inf.readSpace();
    // Read N: length of the arrow (number of '-' characters), 0 <= N <= 10
    int N = inf.readInt(0, 10, "N");
    inf.readEoln();
    // No further lines; end of file
    inf.readEof();
    return 0;
}

#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(0, 500, "M");
    inf.readEoln();

    // Read a, b, X, Y
    int a = inf.readInt(1, N, "a");
    inf.readSpace();
    int b = inf.readInt(1, N, "b");
    inf.readSpace();
    int X = inf.readInt(0, 1000, "X");
    inf.readSpace();
    int Y = inf.readInt(0, 1000, "Y");
    inf.readEoln();

    // Read the M horizontal lines
    for (int i = 0; i < M; i++) {
        // Each p connects vertical p and p+1
        int p = inf.readInt(1, N-1, "p");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}

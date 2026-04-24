#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of vertices
    int N = inf.readInt(3, 10000, "N");
    inf.readEoln();

    // Read N points, each with x and y
    for (int i = 0; i < N; i++) {
        inf.readInt(-100000, 100000, "x_i");
        inf.readSpace();
        inf.readInt(-100000, 100000, "y_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}

#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and C
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int C = inf.readInt(1, 10000, "C");
    inf.readEoln();
    
    // Read C points
    for (int i = 0; i < C; i++) {
        // X coordinate
        int X = inf.readInt(1, N, "X_i");
        inf.readSpace();
        // Y coordinate
        int Y = inf.readInt(1, N, "Y_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

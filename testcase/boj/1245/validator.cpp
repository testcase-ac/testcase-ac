#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 100, "N");
    inf.readSpace();
    int M = inf.readInt(2, 70, "M");
    inf.readEoln();

    // Read the grid of heights
    for (int i = 0; i < N; i++) {
        // Each row has exactly M integers between 0 and 500
        inf.readInts(M, 0, 500, "h");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

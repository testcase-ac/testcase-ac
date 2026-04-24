#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(4, 500, "N");
    inf.readSpace();
    int M = inf.readInt(4, 500, "M");
    inf.readEoln();

    // Read grid values
    for (int i = 0; i < N; i++) {
        // Each row has exactly M integers between 1 and 1000
        inf.readInts(M, 1, 1000, "grid");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

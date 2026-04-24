#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(2, 6, "N");
    inf.readSpace();
    int M = inf.readInt(2, 6, "M");
    inf.readEoln();

    // Read the fuel matrix
    for (int i = 0; i < N; i++) {
        // Each row has exactly M integers in [1,100]
        inf.readInts(M, 1, 100, "fuel");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

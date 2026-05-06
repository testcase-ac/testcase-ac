#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions N and M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read matrix A: N rows, each with M integers in [-100,100]
    for (int i = 0; i < N; i++) {
        inf.readInts(M, -100, 100, "A");
        inf.readEoln();
    }

    // Read matrix B: N rows, each with M integers in [-100,100]
    for (int i = 0; i < N; i++) {
        inf.readInts(M, -100, 100, "B");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

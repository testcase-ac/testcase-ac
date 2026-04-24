#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Read the grid of candies
    for (int i = 0; i < N; i++) {
        inf.readInts(M, 0, 100, "candy");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

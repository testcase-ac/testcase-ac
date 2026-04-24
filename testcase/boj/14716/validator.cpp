#include "testlib.h"
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions M, N
    int M = inf.readInt(1, 250, "M");
    inf.readSpace();
    int N = inf.readInt(1, 250, "N");
    inf.readEoln();

    // Read the grid: M rows, each with N values (0 or 1)
    for (int i = 0; i < M; i++) {
        // We name the row elements based on the row index for clearer error messages
        char name[32];
        sprintf(name, "grid_row_%d", i);
        inf.readInts(N, 0, 1, name);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

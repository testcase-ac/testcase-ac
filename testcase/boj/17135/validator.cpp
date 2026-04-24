#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, D
    int N = inf.readInt(3, 15, "N");
    inf.readSpace();
    int M = inf.readInt(3, 15, "M");
    inf.readSpace();
    int D = inf.readInt(1, 10, "D");
    inf.readEoln();

    // Read grid
    for (int i = 0; i < N; i++) {
        vector<int> row = inf.readInts(M, 0, 1, "grid");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

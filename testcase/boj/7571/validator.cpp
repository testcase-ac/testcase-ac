#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid size N and number of points M
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read M point positions
    for (int i = 0; i < M; i++) {
        // row coordinate
        int r = inf.readInt(1, N, format("r_%d", i).c_str());
        inf.readSpace();
        // column coordinate
        int c = inf.readInt(1, N, format("c_%d", i).c_str());
        inf.readEoln();
    }

    // No extra data allowed
    inf.readEof();
    return 0;
}
